//library
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

using namespace std;

//parent class
class Menu {
	public:
	//atribut class
	string nama;
	int harga, saldo, opsi, jumlah, pilih;

	//constructor default
	Menu() {
		this;
	}
	//constructor 1
	Menu(int _pilih, int _jumlah) {
 		pilih = _pilih;
		jumlah = _jumlah;
	}

	//pointer untuk linked list
	Menu *next, *prev, *head, *tail, *cur, *newNode, *afterNode, *del;

	//deklarasi dan inisialisasi linked list untuk pertama kali
	void createLinkedList(string nama, int harga) {

		head = new Menu();
		head->nama = nama;
		head->harga = harga;
		head->prev = NULL;
		head->next = NULL;
		tail = head;
	}
	
	//menghitung jumlah node linked list
	int countLinkedList() {

		cur = head;
		int jumlah = 0;
			
		while(cur != NULL) {
			jumlah++;
			cur = cur->next;
		}
		
		return jumlah;
	}
	
	
	//menambah node baru ke linked list
	void addMenuItem(string nama, int harga) {
		
		newNode = new Menu();
		newNode->nama = nama;
		newNode->harga = harga;
		newNode->prev = tail;
		newNode->next = NULL;
		
		tail->next = newNode;
		tail = newNode;
	}
	
	//memperbarui nilai atribut dalam satu node linked list
	void updateMenuItem(string nama, int harga, int posisi) {
	
		//posisi diluar jangkauan
		if (posisi < 1 || posisi > countLinkedList()) {
			cout << "Posisi di luar jangkauan" << endl;
			
		//node posisi pertama
		} else if (posisi == 1) {
			head->nama = nama;
			head->harga = harga;
			
		//node posisi terakhir
		} else if (posisi == countLinkedList()) {
			tail->nama = nama;
			tail->harga = harga;
			
		//node posisi tengah
		} else {
			cur = head;
			int nomor = 1;

			while (nomor < posisi) {
				cur = cur->next;
				nomor++;
			}
			
			cur->nama = nama;
			cur->harga = harga;
		}
		
	}
	
	//menghapus satu node linked list
	void deleteMenuItem(int posisi) {
		
		//posisi diluar jangkauan
		if (posisi < 1 || posisi > countLinkedList()) {
			cout << "Posisi di luar jangkauan" << endl;

		//node posisi pertama
		} else if (posisi == 1) {
			del = head;
			head = head->next;
			if (countLinkedList() != 0) {	
				head->prev = NULL;
			}
			delete del;

		//node posisi terakhir				
		} else if(posisi == countLinkedList()){
			del = tail;
			tail = tail->prev;
			tail->next = NULL;
			delete del;

		//node posisi tengah			
		} else {
			int nomor = 1;
			cur = head;
			
			while (nomor < posisi - 1) {
				cur = cur->next;
				nomor++;
			}

			del = cur->next;
			afterNode = del->next;
			cur->next = afterNode;
			afterNode->prev = cur;
			delete del;
		}
	}
	
	//menampilkan semua node linked list dengan function overloading printMenuItem()
	void printMenuItem() {
		
		if (head != NULL) {	
			cout << "=============================================" << endl;
			cout << "           Jumlah menu saat ini: " << countLinkedList() << endl;
			cout << "=============================================" << endl;
		} else {
			cout << "=============================================" << endl;
			cout << "              Tidak ada menu" << endl;
			cout << "=============================================" << endl;
		}

		cur = head;
		int nomor = 1;
		while (cur != NULL) {
			cout << nomor << ". " << cur->nama << " dengan harga " << cur->harga << endl;
			
			cur = cur->next;
			nomor++;
		}	
			
		cout << endl;
		
	}
	
	//menampilkan satu spesifik node linked list dengan function overloading printMenuItem()
	void printMenuItem(int posisi) {
		
		cur = head;
		int nomor = 1;
	
		while (nomor < posisi) {	
			
			cur = cur->next;
			nomor++;
		}
		
		cout << cur->nama << " dengan harga " << cur->harga << endl;
	}
	
	//menampilkan detail/deskripsi pemesanan 
	void printOrderDetails(vector<Menu> order) {

		int nomor = 1;
		cur = head;
		
		for (int i=0; i<order.size(); i++) {
			
			while (nomor < order[i].pilih) {
				cur = cur->next;
				nomor++;
			}
			
			while (nomor > order[i].pilih) {
				cur = cur->prev;
				nomor--;
			}

			if (nomor == order[i].pilih) {
				cout << i+1 << ". " << cur->nama << " dengan harga " << cur->harga << " berjumlah " << order[i].jumlah << endl;
			}
		}
		
		cout << endl;
	}
};

//memvalidasi input user
int checkInput(int input) {
	
	while (!(cin >> input)) {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Input harus berupa angka. Silakan coba lagi: ";	
	}
	
	return input;
}

//membersihkan tampilan di console
void clearConsole() {

	cout << endl;
	
	for (int j = 0; j < 3; j++) {
	   	cout << "\rLoading   \rLoading";
	   	 
		for (int i = 0; i < 3; i++) {
	       cout << ".";
	       Sleep(150);
	   	}
	}
	
	system("cls");
}

template<typename T>

//menambah item menu makanan ke vector yang akan dioperasikan di linked list
vector<T> & operator << (vector<T> & v, Menu const item){

	v.push_back(item);
			
	return v;
}
	
//static boolean untuk membantu memanggil default item sekali saja
static bool defaultItem;

//child class dari parent class Menu
class MenuItem: public Menu {
	
	public:
	//deklarasi vector order untuk menampung menu apa saja yang dipilih pembeli
	vector<Menu> order;

	//method untuk menampilkan daftar menu
	void showItemList() {

		clearConsole();
		
		if (!defaultItem) {
			defaultItem = true;
			createLinkedList("Mie Ayam", 10000);
			addMenuItem("Nasi Goreng", 15000);
			addMenuItem("Es Teh", 5000);
			addMenuItem("Air Mineral", 3000);
		} 
		
		printMenuItem();
	}
	
	//method untuk mengedit item menu
	void editItem() {

		showItemList();
		
		cout << "=============================================" << endl;
		cout << "1. Tambah item menu\n2. Ubah detail menu\n3. Hapus item menu\n4. Exit" << endl; 
		cout << "=============================================" << endl;
		opsi = checkInput(opsi);
		
		switch(opsi) {
			case 1:
				addItem();
				editItem();
				break;
				
			case 2:
				updateItem();
				editItem();
				break;
				
			case 3:
				deleteItem();
				editItem();
				break;
				
			case 4:
				break;		
						
			default:
				cout << "Input yang diberikan tidak valid" << endl;
				editItem();
		}
	}
	
	//method untuk menambahkan item menu
	void addItem() {

		cout << "Nama item: ";
		cin >> ws;
		getline(cin, nama);
		
		cout << "Harga item: Rp";
		harga = checkInput(harga); 
		
		if (countLinkedList() == 0) {
			createLinkedList(nama, harga);
		} else {
			addMenuItem(nama, harga);	
		}
	
		cout << "Item berhasil ditambahkan ke daftar menu" << endl;
	}
	
	//method untuk memperbarui item menu
	void updateItem() {
		
		cout << endl << "Pilih item menu yang ingin diubah: " << endl;
		
		opsi = checkInput(opsi);
		
		if (countLinkedList()>0) {
			
			printMenuItem(opsi);
			
			cout << "Ubah nama: "; 
			cin >> ws;
			getline(cin , nama);
								
			cout << "Ubah harga: Rp"; 
			harga = checkInput(harga);
				
			updateMenuItem(nama, harga, opsi);
			cout << "Item menu berhasil diubah" << endl;
			
		} else {
			cout << "Tidak ada menu" << endl;
		}
	}
	
	//method untuk menghapus item menu
	void deleteItem() {

		cout << endl << "Pilih item menu yang ingin dihapus: " << endl;
		opsi = checkInput(opsi);
		
		deleteMenuItem(opsi);
	}
	
	//method untuk memilih item menu pada saat order
	void selectItem() {

		cout << "Pilih item menu: " << endl;
		
		pilih = checkInput(pilih);
	
		if(pilih < 1 || pilih > countLinkedList()) {
			cout << "Item menu yang Anda masukan tidak tersedia" << endl;
			selectItem();
			
		} else {		
			cout << "Jumlah yang ingin dipesan: ";
			jumlah = checkInput(jumlah);
					
			//penggunaan overloading operator << di method selectItem()
			order << Menu(pilih, jumlah);
			
			cout << endl;	
		}
		
		cout << "=============================================" << endl;
		cout << "Pilih lagi? " << "\n1. Ya\n2. Tidak" << endl;
		opsi = checkInput(opsi);
	
		switch(opsi) {
			case 1:
				selectItem();
				break;
				
			case 2:
				showPaymentDetail();
				break;
				
			default:
				cout << "Item menu yang Anda masukan tidak tersedia" << endl;
				selectItem();
				break;
		}
	}
	
	//method untuk menghitung total harga pesanan
	int countTotalPrice() {

		int sum = 0;
		
		cur = head;
		int nomor = 1;
		
		for (int i=0; i<order.size(); i++) {
			
			while (nomor < order[i].pilih) {
				cur = cur->next;
				nomor++;
			}
			
			while (nomor > order[i].pilih) {
				cur = cur->prev;
				nomor--;
			}
		
			if (nomor == order[i].pilih) {
				sum += cur->harga * order[i].jumlah;
			}
	
		}
		
		return sum;
	}
	
	//method untuk mengecek saldo dan kembalian pesanan
	int countSisaSaldo(int _saldo) {

		saldo = _saldo;
		int total = countTotalPrice();
	
		if (total > saldo) {
			cout << endl << "Saldo Anda (Rp"<< saldo << ") tidak cukup" << endl;
			order.clear();
			return 0;
			
		} else {
			int sisaSaldo = saldo - total;
			saldo = sisaSaldo;
			
			return sisaSaldo;
		}
	}	
	
	//method untuk menampilkan detail pemesanan
	void showPaymentDetail() {

		clearConsole();
		cout << "=============================================" << endl;
		cout << "            Deskripsi pemesanan: " << endl;
		cout << "=============================================" << endl;
		
		printOrderDetails(order);			
			
		cout << "Saldo Anda adalah Rp" << saldo << endl;			
		cout << "Total yang harus dibayar: Rp" << countTotalPrice() << endl;
		cout << "=============================================" << endl;
		cout << "\nLakukan pembayaran?\n1. Ya\n2. Batal" << endl;
		cout << "=============================================" << endl;
		
		opsi = checkInput(opsi);
		
		switch(opsi) {
			case 1:
				cout << "Kembalian Anda adalah Rp" << countSisaSaldo(saldo) << endl;
				cout << "Terima kasih sudah mampir ke restoran serba ada PBO A081" << endl << endl;
				order.clear();
				break;
				
			case 2:
				cout << "Pembayaran dibatalkan" << endl << endl;				
				order.clear();
				break;
				
			default:
				cout << "Input yang diberikan tidak valid" << endl;
		} 
	}
};

//deklarasi objek menu, dideklarasi di luar main class agar bisa diakses secara global
MenuItem menu;

//function untuk mengembalikan ke tampilan awal program
void backToHomeScreen() {

	int opsi;
	
	cout << "Kembali ke halaman utama? \n1. Ya\n2. Tidak" << endl;
	cout << "=============================================" << endl;
	opsi = checkInput(opsi);
		
	switch(opsi) {
		case 1:
			break;
			
		case 2:
			menu.showItemList();
		
			if (menu.countLinkedList()>0){
				menu.selectItem();
			}
			
			backToHomeScreen();
			break;
			
		default:
			cout << "Input tidak sesuai" << endl << endl;
			backToHomeScreen();
	}	
}	
	
main() {
	clearConsole();
	
	int opsi;
	cout << "=============================================" << endl;
	cout << "Selamat datang di restoran serba ada PBO A081! " << endl <<
	"Masuk sebagai:\n1. Pembeli\n2. Admin" << endl;
	cout << "=============================================" << endl;
	opsi = checkInput(opsi);
	
	//beroperasi berdasarkan input user dan mengeksekusi method pada class yang dipanggil
	switch (opsi) {
		case 1:
			int saldo;
			cout << "Masukkan saldo yang Anda miliki: ";
			saldo = checkInput(saldo);
		
			if (saldo > 0) {
				menu.countSisaSaldo(saldo);
				menu.showItemList();
					
				if (menu.countLinkedList()>0){
					menu.selectItem();
				}
			}
			
			backToHomeScreen();
			main();
			break;
			
		case 2:
			menu.showItemList();
			menu.editItem();
			main();
			break;
			
		default:
			cout << "Input yang diberikan tidak valid" << endl;
			main();
	}
}

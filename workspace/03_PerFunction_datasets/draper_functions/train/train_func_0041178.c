addressbook_impl(void) {

  if (!AddressBook::get_is_address_list()) {
    AddressBook* dialog_p = new AddressBook(standard_size, get_win());

    dialog_p->accepted.connect(Callback::make(*this, &MainWindow::set_number_cb));


  }
}

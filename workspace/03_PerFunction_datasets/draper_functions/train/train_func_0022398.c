add_folder_prompt(void) {

  AddFolderDialog* dialog_p = new AddFolderDialog(standard_size, get_win());
  dialog_p->accepted.connect(Callback::make(*this, &FaxListDialog::add_folder));


}

button_clicked_cb(unsigned x) {
  std::string str(buttons[x]->get_label());
  signal_button_clicked.emit(str);
}

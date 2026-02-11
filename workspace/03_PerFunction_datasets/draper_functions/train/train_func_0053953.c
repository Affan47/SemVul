menu(char *str, Gtk::Menu *menu) {
  Gtk::Menu *m = Gtk::manage(new Gtk::Menu());
  if (menu) {
    menu->items().push_back(Gtk::Menu_Helpers::MenuElem(str, *m));
  }
  else {
    items().push_back(Gtk::Menu_Helpers::MenuElem(str, *m));
  }
  return m;
}

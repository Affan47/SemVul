item(Gtk::Menu *menu, const Gtk::StockID& stock_id, guint key, Gdk::ModifierType mod) {

  Gtk::AccelKey _key(key, mod);
  menu->items().push_back(Gtk::Menu_Helpers::StockMenuElem(stock_id, _key));
  return &menu->items().back();
}

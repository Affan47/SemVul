add(const Gtk::StockID& stock_id, const std::string& filename) {
	Glib::RefPtr<Gdk::Pixbuf> pixbuf = load_from_file(filename);
	if(!pixbuf) {
		std::cerr << "unable to load file " << filename << std::endl;
		return;
	}
	Gtk::IconSet* set = new Gtk::IconSet(pixbuf);
	m_iconset.push_back(set);
	Gtk::IconFactory::add(stock_id, *set);
}

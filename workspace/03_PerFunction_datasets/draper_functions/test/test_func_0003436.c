update() {
    g_assert(_widget != NULL);
    static_cast<Gtk::SpinButton*>(_widget)->update();
}

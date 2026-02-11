signal_auto_spell_activate_cb() {
  signal_auto_spell_activate.emit(dynamic_cast<Gtk::CheckMenuItem *>(_auto_spell)->get_active());
}

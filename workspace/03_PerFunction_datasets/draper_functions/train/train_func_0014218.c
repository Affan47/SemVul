on_erase(const Gtk::TextBuffer::iterator& start, const Gtk::TextBuffer::iterator& end) {
  _erase = end.get_line();
  _deleted = get_text(start, end, false);
#ifdef GLIBMM_DEFAULT_SIGNAL_HANDLERS_ENABLED
  Gtk::TextBuffer::on_erase(start, end);
#endif
}

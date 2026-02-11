search_activate_cb() {
  if (_search.get_text().size()) {
    signal_search_activated.emit(_search.get_text());
  }
}

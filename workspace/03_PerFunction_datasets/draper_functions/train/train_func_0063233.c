get_lines(Gtk::TextIter& start, Gtk::TextIter& end, std::vector<Glib::ustring>& l) {
  Gtk::TextIter dummy;
  while (start <= end) {
    dummy = start;
    if (!dummy.ends_line()) {
      dummy.forward_to_line_end();
    }

    l.push_back(_text_view.get_buffer()->get_text(start, dummy, false));

    if (!start.forward_line()) {
      break;
    }
  }
}

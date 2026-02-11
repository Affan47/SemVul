spell_checker_worker() {

  if (spell_checker_has_lines()) {

    Gtk::TextIter iter;
    spell_checker_get_line(iter);

    spell_checker_check(iter);
    lines[iter.get_line()] = false;
  }
  else {
    spell_worker_conn.disconnect();
  }

  return true;
}

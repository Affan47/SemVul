replace_dialog_signal_replace_all_cb(ReplaceDialog *dialog) {
  Document *doc = get_active();
  assert(doc != NULL);
  int x = 0;

  doc->set_search_whole_word(dialog->whole_word());
  doc->set_search_match_case(dialog->match_case());
  doc->set_search_backwards(dialog->backwards());
  doc->set_search_from_beginning(dialog->beginning());
  doc->set_search_text(dialog->get_text());
  doc->set_replace_text(dialog->get_replace());


  doc->set_search_wrap(false);

  while (doc->search()) {
    ++x;
    doc->replace();
  }
  katoob_info(Utils::substitute(ngettext("Replaced %d occurence.", "Replaced %d occurences.", x), x));
}

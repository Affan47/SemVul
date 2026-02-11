read_words(wistream& is) {
  while(!is.eof()) {
    wstring w;
    getline(is,w);
    w=StringUtils::tolower(w);
    if (w.length()>0) {
      words.insert(w);
      new_word_register(w);
    }
  }
  n_set=words.size();
  wcerr<<L"# words: "<<n_set<<L"\n";
}

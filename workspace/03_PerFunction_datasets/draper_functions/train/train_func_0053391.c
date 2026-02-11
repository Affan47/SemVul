SerializeStrings() {
  List<HashMap::Entry*> sorted_strings;
  SortHashMap(&strings_, &sorted_strings);
  writer_->AddString("\"<dummy>\"");
  for (int i = 0; i < sorted_strings.length(); ++i) {
    writer_->AddCharacter(',');
    SerializeString(
        reinterpret_cast<const unsigned char*>(sorted_strings[i]->key));
    if (writer_->aborted()) return;
  }
}

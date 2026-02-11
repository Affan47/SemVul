useStringTable(bool Thin, StringRef Name) {
  return Thin || Name.size() >= 16;
}

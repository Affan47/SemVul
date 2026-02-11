UpdateColumns(const string &str, int column) {

  size_t last_newline = str.rfind('\n');


  if (last_newline == string::npos) {
    return static_cast<int>(column + str.size() +
                            strlen(kDirectiveBegin) + strlen(kDirectiveEnd));


  } else {
    return static_cast<int>(str.size() + strlen(kDirectiveEnd) - last_newline);
  }
}

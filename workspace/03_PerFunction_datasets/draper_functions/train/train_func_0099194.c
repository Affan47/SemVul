ParseIdentifierNameOrGetOrSet(bool* is_get,
                                                               bool* is_set,
                                                               bool* ok) {
  Identifier result = ParseIdentifierName(ok);
  if (!*ok) return Identifier::Default();
  if (scanner_->is_literal_ascii() &&
      scanner_->literal_length() == 3) {
    const char* token = scanner_->literal_ascii_string().start();
    *is_get = strncmp(token, "get", 3) == 0;
    *is_set = !*is_get && strncmp(token, "set", 3) == 0;
  }
  return result;
}

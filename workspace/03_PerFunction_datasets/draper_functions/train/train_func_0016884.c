ParseIdentifierNameOrGetOrSet(bool* is_get,
                                                     bool* is_set,
                                                     bool* ok) {
  Handle<String> result = ParseIdentifierName(ok);
  if (!*ok) return Handle<String>();
  if (scanner().is_literal_ascii() && scanner().literal_length() == 3) {
    const char* token = scanner().literal_ascii_string().start();
    *is_get = strncmp(token, "get", 3) == 0;
    *is_set = !*is_get && strncmp(token, "set", 3) == 0;
  }
  return result;
}

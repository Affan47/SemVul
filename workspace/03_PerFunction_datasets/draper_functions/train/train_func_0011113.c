to_utf8(const char* str) {
  static char* result = NULL;
  if (result) g_free(result);
  result = g_locale_to_utf8(str, -1, NULL, NULL, NULL);
  return result;
}

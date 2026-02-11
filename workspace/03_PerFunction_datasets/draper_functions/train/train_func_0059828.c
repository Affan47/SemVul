str_ends_with(const char * string, const char * suffix) {
  size_t string_length = strlen(string);
  size_t suffix_length = strlen(suffix);
  if (string_length < suffix_length) {
    return false;
  }
  return strcmp(string + string_length - suffix_length, suffix) == 0;
}

Swig_file_suffix(const_String_or_char_ptr filename) {
  char *d;
  char *c = Char(filename);
  int len = Len(filename);
  if (strlen(c)) {
    d = c + len - 1;
    while (d != c) {
      if (*d == '.')
	return d;
      d--;
    }
    return c + len;
  }
  return c;
}

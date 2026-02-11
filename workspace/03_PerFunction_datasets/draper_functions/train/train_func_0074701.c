SWIG_UnpackData(const char *c, void *ptr, size_t sz) {
  register unsigned char *u = (unsigned char *) ptr;
  register const unsigned char *eu = u + sz;
  for (; u != eu; ++u) {
    register char d = *(c++);
    register unsigned char uu;
    if ((d >= '0') && (d <= '9'))
      uu = ((d - '0') << 4);
    else if ((d >= 'a') && (d <= 'f'))
      uu = ((d - ('a'-10)) << 4);
    else
      return (char *) 0;
    d = *(c++);
    if ((d >= '0') && (d <= '9'))
      uu |= (d - '0');
    else if ((d >= 'a') && (d <= 'f'))
      uu |= (d - ('a'-10));
    else
      return (char *) 0;
    *u = uu;
  }
  return c;
}

packet_string_copy(char *dst,char *src) {
  char *p = src,*q = dst;
  while (*p != '\0' && q < (dst+MAXSTRINGSIZE)) {
    *q++ = *p++;
  }
  *q = '\0';
  return q - dst;
}

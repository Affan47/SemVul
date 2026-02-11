lowercase(char *s, size_t len){
  unsigned char *c, *e;

  c = (unsigned char*)s;
  e = c+len;

  while(c < e){
    *c = TOLOWER((unsigned char)(*c));
    c++;
  }
  return s;
}

addstring (char **buf, int *blen, int *maxlen, char *str)
#else
static void addstring(buf, blen, maxlen, str)
     char **buf;
     int *blen;
     int *maxlen;
     char *str;
#endif
{
  int slen;

  slen = strlen(str) + 1;
  while( (*blen + slen) >= *maxlen ){
    *maxlen += BUFINC;
    *buf = (char *)xrealloc(*buf, *maxlen);
  }
  strcat(*buf, str);
  *blen += slen;
}

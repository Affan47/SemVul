GWEN_Text_CountUtf8Chars(const char *s, int len) {
  int count;
  int handled;

  if (len==0)
    len=strlen(s);
  count=0;
  handled=0;
  while(handled<len) {
    unsigned char c;
    int i;

    c=(unsigned char)*s;
    if ((c & 0xfe)==0xfc)
      i=5;
    else if ((c & 0xfc)==0xf8)
      i=4;
    else if ((c & 0xf8)==0xf0)
      i=3;
    else if ((c & 0xf0)==0xe0)
      i=2;
    else if ((c & 0xe0)==0xc0)
      i=1;
    else if (c & 0x80) {
      DBG_ERROR(GWEN_LOGDOMAIN, "Invalid UTF8 character at pos %d", handled);
      return -1;
    }
    else
      i=0;
    if (handled+i+1>len) {
      DBG_ERROR(GWEN_LOGDOMAIN,
                "Incomplete UTF8 sequence at pos %d", handled);
      return -1;
    }
    s++;
    if (i) {
      int j;

      for (j=0; j<i; j++) {
        if ((((unsigned char)*s) & 0xc0)!=0xc0) {
          DBG_ERROR(GWEN_LOGDOMAIN,
                    "Invalid UTF8 sequence at pos %d (rel %d of %d)",
                    handled, j, i);
        }
        s++;
      }
    }
    handled+=i+1;
    count++;
  }

  return count;
}

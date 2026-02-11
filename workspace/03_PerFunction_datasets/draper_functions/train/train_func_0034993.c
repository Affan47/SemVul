GWEN_Text_FromHexBuffer(const char *src, GWEN_BUFFER *buf) {
  while(*src) {
    unsigned char d1, d2;
    unsigned char c;


    if (isspace((int)*src)) {
      src++;
    }
    else {
      if (!isxdigit((int)*src)) {
        DBG_ERROR(GWEN_LOGDOMAIN, "Bad char in hex string");
        return -1;
      }
      d1=(unsigned char)(toupper(*src));


      src++;
      if (!(*src) || !isxdigit((int)*src)) {
        DBG_ERROR(GWEN_LOGDOMAIN, "Incomplete hex byte (only 1 digit)");
        return -1;
      }
      d2=(unsigned char)(toupper(*src));
      src++;


      d1-='0';
      if (d1>9)
        d1-=7;
      c=(d1<<4)&0xf0;
      d2-='0';
      if (d2>9)
        d2-=7;
      c+=(d2&0xf);

      GWEN_Buffer_AppendByte(buf, (char)c);
    }
  }

  return 0;
}

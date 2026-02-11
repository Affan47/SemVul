GWEN_Base64_Decode(const unsigned char *src, unsigned int size,
                       GWEN_BUFFER *dst) {
  unsigned int i;
  const char *p = "0";
  uint32_t v;
  int lastWasEq;
  int sizeGiven;


  sizeGiven=(size!=0);
  lastWasEq=0;
  for (;;) {
    if ((sizeGiven && size==0) || lastWasEq || !*src)
      break;
    v=0;

    while (*src && ((p=strchr(GWEN_Base64_Alphabet, *src))==0))
      src++;
    if (!*src)
      break;
    for (i=0; i<4; i++) {

      if (lastWasEq) {
	while (*src && *src!='=')
	  src++;
      }
      else {
        while (*src && ((p=strchr(GWEN_Base64_Alphabet, *src))==0))
          src++;
      }
      if (!*src) {
        if (i==0 && !sizeGiven) {
          return 0;
        }
        else {
          DBG_ERROR(GWEN_LOGDOMAIN, "Premature end reached (%d)", i);
          return -1;
        }
      }
      if (*src=='=')
        lastWasEq++;
      v<<=6;
      v+=(p-GWEN_Base64_Alphabet) & 0x3f;
      src++;
    }


    if (sizeGiven) {
      switch(size) {
      case 1:
        GWEN_Buffer_AppendByte(dst, (v>>16) & 0xff);
        size--;
        break;
      case 2:
        GWEN_Buffer_AppendByte(dst, (v>>16) & 0xff);
        GWEN_Buffer_AppendByte(dst, (v>>8) & 0xff);
        size-=2;
        break;
      default:
        GWEN_Buffer_AppendByte(dst, (v>>16) & 0xff);
        GWEN_Buffer_AppendByte(dst, (v>>8) & 0xff);
        GWEN_Buffer_AppendByte(dst, v & 0xff);
        size-=3;
        break;
      }
    }
    else {
      int bytes;

      bytes=(24-(lastWasEq*6))/8;
      if (bytes) {
	GWEN_Buffer_AppendByte(dst, (v>>16) & 0xff);
	if (bytes>1) {
	  GWEN_Buffer_AppendByte(dst, (v>>8) & 0xff);
          if (bytes>2)
	    GWEN_Buffer_AppendByte(dst, v & 0xff);
	}
      }
    }
  }

  return 0;
}

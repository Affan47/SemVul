GWEN_Base64_Encode(const unsigned char *src, unsigned int size,
                       GWEN_BUFFER *dst,
                       unsigned int maxLineLength) {
  unsigned int by3;
  unsigned int i;
  unsigned int l;
  uint32_t triplet;
  unsigned char c1, c2, c3, c4;

  if (maxLineLength) {
    if (maxLineLength<4) {
      DBG_ERROR(GWEN_LOGDOMAIN, "I need at least 4 bytes per line");
      return -1;
    }
  }

  by3=size/3;

  l=0;
  for (i=0; i<by3; i++) {
    triplet=(src[0]<<16)+(src[1]<<8)+src[2];
    src+=3;
    c4=triplet & 0x3f;
    triplet>>=6;
    c3=triplet & 0x3f;
    triplet>>=6;
    c2=triplet & 0x3f;
    triplet>>=6;
    c1=triplet & 0x3f;
    if (maxLineLength) {
      if (l+4>maxLineLength) {
        GWEN_Buffer_AppendByte(dst, '\n');
        l=0;
      }
      l+=4;
    }
    GWEN_Buffer_AppendByte(dst, GWEN_Base64_Alphabet[c1]);
    GWEN_Buffer_AppendByte(dst, GWEN_Base64_Alphabet[c2]);
    GWEN_Buffer_AppendByte(dst, GWEN_Base64_Alphabet[c3]);
    GWEN_Buffer_AppendByte(dst, GWEN_Base64_Alphabet[c4]);
  }
  if (maxLineLength) {
    if (l+4>=maxLineLength) {
      GWEN_Buffer_AppendByte(dst, '\n');
      l=0;
    }
  }


  switch(size % 3) {
  case 0:

    break;

  case 1:

    triplet=(src[0]<<4);
    c2=triplet & 0x3f;
    triplet>>=6;
    c1=triplet & 0x3f;
    GWEN_Buffer_AppendByte(dst, GWEN_Base64_Alphabet[c1]);
    GWEN_Buffer_AppendByte(dst, GWEN_Base64_Alphabet[c2]);
    GWEN_Buffer_AppendString(dst, "==");
    break;

  case 2:

    triplet=(src[0]<<10)+(src[1]<<2);
    c3=triplet & 0x3f;
    triplet>>=6;
    c2=triplet & 0x3f;
    triplet>>=6;
    c1=triplet & 0x3f;
    GWEN_Buffer_AppendByte(dst, GWEN_Base64_Alphabet[c1]);
    GWEN_Buffer_AppendByte(dst, GWEN_Base64_Alphabet[c2]);
    GWEN_Buffer_AppendByte(dst, GWEN_Base64_Alphabet[c3]);
    GWEN_Buffer_AppendByte(dst, '=');
    break;

  default:
    break;
  }

  return 0;
}

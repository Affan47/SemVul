GWEN_Text_EscapeXmlToBuffer(const char *src, GWEN_BUFFER *buf) {
  while(*src) {
    unsigned char x;
    const GWEN_TEXT_ESCAPE_ENTRY *e;
    int match;

    match=0;
    x=(unsigned char)*src;
    e=gwen_text__xml_escape_chars;
    while(e->replace) {
      if (x==e->character) {
        GWEN_Buffer_AppendString(buf, e->replace);
        match=1;
        break;
      }
      e++;
    }

    if (!match) {
      if (0 && x>127) {
	char numbuf[32];

	snprintf(numbuf, sizeof(numbuf), "&#%d;", x);
        GWEN_Buffer_AppendString(buf, numbuf);
      }
      else
	GWEN_Buffer_AppendByte(buf, *src);
    }
    src++;
  }

  return 0;
}

readEmbFontFile(XRef *xref, int *len) {
  char *buf;
  Object obj1, obj2;
  Stream *str;
  int c;
  int size, i;

  obj1.initRef(embFontID.num, embFontID.gen);
  obj1.fetch(xref, &obj2);
  if (!obj2.isStream()) {
    error(-1, "Embedded font file is not a stream");
    obj2.free();
    obj1.free();
    embFontID.num = -1;
    *len = 0;
    return NULL;
  }
  str = obj2.getStream();

  buf = NULL;
  i = size = 0;
  str->reset();
  while ((c = str->getChar()) != EOF) {
    if (i == size) {
      size += 4096;
      buf = (char *)grealloc(buf, size);
    }
    buf[i++] = c;
  }
  *len = i;
  str->close();

  obj2.free();
  obj1.free();

  return buf;
}

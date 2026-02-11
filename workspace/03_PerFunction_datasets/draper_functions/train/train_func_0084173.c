writeRawStream (Stream* str, OutStream* outStr)
{
  Object obj1;
  str->getDict()->lookup("Length", &obj1);
  if (!obj1.isInt()) {
    error (-1, "PDFDoc::writeRawStream, no Length in stream dict");
    return;
  }

  const int length = obj1.getInt();
  obj1.free();

  outStr->printf("stream\r\n");
  str->unfilteredReset();
  for (int i=0; i<length; i++) {
    int c = str->getUnfilteredChar();
    outStr->printf("%c", c);
  }
  str->reset();
  outStr->printf("\r\nendstream\r\n");
}

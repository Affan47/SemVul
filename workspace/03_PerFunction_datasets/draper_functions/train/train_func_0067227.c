saveWithoutChangesAs(OutStream *outStr) {
  int c;

  str->reset();
  while ((c = str->getChar()) != EOF) {
    outStr->put(c);
  }
  str->close();

  return errNone;
}

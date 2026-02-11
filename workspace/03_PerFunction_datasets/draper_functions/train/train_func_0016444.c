jslPrintTokenLineMarker(vcbprintf_callback user_callback, void *user_data, struct JsLex *lex, size_t tokenPos) {
  size_t line = 1,col = 1;
  jsvGetLineAndCol(lex->sourceVar, tokenPos, &line, &col);
  size_t startOfLine = jsvGetIndexFromLineAndCol(lex->sourceVar, line, 1);
  size_t lineLength = jsvGetCharsOnLine(lex->sourceVar, line);

  if (lineLength>60 && tokenPos-startOfLine>30) {
    cbprintf(user_callback, user_data, "...");
    size_t skipChars = tokenPos-30 - startOfLine;
    startOfLine += 3+skipChars;
    col -= skipChars;
    lineLength -= skipChars;
  }


  int chars = 0;
  JsvStringIterator it;
  jsvStringIteratorNew(&it, lex->sourceVar, startOfLine);
  while (jsvStringIteratorHasChar(&it) && chars<60) {
    char ch = jsvStringIteratorGetChar(&it);
    if (ch == '\n') break;
    char buf[2];
    buf[0] = ch;
    buf[1] = 0;
    user_callback(buf, user_data);
    chars++;
    jsvStringIteratorNext(&it);
  }
  jsvStringIteratorFree(&it);

  if (lineLength > 60)
    user_callback("...", user_data);
  user_callback("\n", user_data);
  while (col-- > 0) user_callback(" ", user_data);
  user_callback("^\n", user_data);
}

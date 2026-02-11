yy_scan_newlines(const char* text, struct yyguts_t* yyg) {
  for (; *text; ++text) {
    if (*text == '\r') {
      if (text[1] == '\n') {
        ++text;
      }
      ++yyextra->lineno;
    } else if (*text == '\n') {
      ++yyextra->lineno;
    }
  }
}

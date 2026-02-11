test_string2() {
  setup_test("\"\"\"");
  return yylex() == TK_STRING && strcmp(yylval.sval, "") == 0 && yylex() == ERR_SCAN;
}

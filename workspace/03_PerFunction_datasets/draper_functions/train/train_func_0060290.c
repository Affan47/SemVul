test_string8() {
  setup_test("\"\"a\"");
  return yylex() == TK_STRING && strcmp(yylval.sval, "") == 0 && yylex() == TK_ID && strcmp(yylval.sval, "a") == 0 &&
	  yylex() == ERR_SCAN;
}

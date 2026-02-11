test_id2() {
  setup_test("foo_bar= abc!234 k;x");
  return yylex() == TK_ID && strcmp(yylval.sval, "foo_bar") == 0 &&
	  yylex() == '=' && yylex() == TK_ID && strcmp(yylval.sval, "abc") == 0 &&
	  yylex() == '!' && yylex() == TK_INT && yylval.ival == 234 &&
	  yylex() == TK_ID  && strcmp(yylval.sval, "k") == 0 && yylex() == ';' &&
	  yylex() == TK_ID && strcmp(yylval.sval, "x") == 0;
}

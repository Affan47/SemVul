yy_syntax_error(
  yyParser *yypParser,
  int yymajor,
  YYMINORTYPE yyminor
){
  ParseARG_FETCH;
#define TOKEN (yyminor.yy0)
#line 48 "parser.lem"
 Error("Syntax Error"); *solution = sqrtf(-1.f);
#line 1522 "parser.c"
  ParseARG_STORE;
}

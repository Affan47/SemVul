yy_Symbol()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "Symbol"));  yyText(yybegin, yyend);  if (!(YY_BEGIN)) goto l447;  if (!yy_SpecialChar()) goto l447;  yyText(yybegin, yyend);  if (!(YY_END)) goto l447;  yyDo(yy_1_Symbol, yybegin, yyend);
  yyprintf((stderr, "  ok   %s @ %s\n", "Symbol", yybuf+yypos));
  return 1;
  l447:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "Symbol", yybuf+yypos));
  return 0;
}

yy_TerminalEndline()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "TerminalEndline"));  if (!yy_Sp()) goto l299;  if (!yy_Newline()) goto l299;  if (!yy_Eof()) goto l299;  yyDo(yy_1_TerminalEndline, yybegin, yyend);
  yyprintf((stderr, "  ok   %s @ %s\n", "TerminalEndline", yybuf+yypos));
  return 1;
  l299:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "TerminalEndline", yybuf+yypos));
  return 0;
}

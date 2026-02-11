yy_Apostrophe()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "Apostrophe"));  if (!yymatchChar('\'')) goto l39;  yyDo(yy_1_Apostrophe, yybegin, yyend);
  yyprintf((stderr, "  ok   %s @ %s\n", "Apostrophe", yybuf+yypos));
  return 1;
  l39:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "Apostrophe", yybuf+yypos));
  return 0;
}

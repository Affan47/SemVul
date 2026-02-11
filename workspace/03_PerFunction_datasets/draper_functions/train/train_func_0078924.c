yy_trailer()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "trailer"));  if (!yymatchString("%%")) goto l96;  yyText(yybegin, yyend);  if (!(YY_BEGIN)) goto l96;
  l97:;
  {  int yypos98= yypos, yythunkpos98= yythunkpos;  if (!yymatchDot()) goto l98;  goto l97;
  l98:;	  yypos= yypos98; yythunkpos= yythunkpos98;
  }  yyText(yybegin, yyend);  if (!(YY_END)) goto l96;  yyDo(yy_1_trailer, yybegin, yyend);
  yyprintf((stderr, "  ok   %s @ %s\n", "trailer", yybuf+yypos));
  return 1;
  l96:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "trailer", yybuf+yypos));
  return 0;
}

yy_TitleSingle()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "TitleSingle"));  if (!yymatchChar('\'')) goto l164;  yyText(yybegin, yyend);  if (!(YY_BEGIN)) goto l164;
  l165:;
  {  int yypos166= yypos, yythunkpos166= yythunkpos;
  {  int yypos167= yypos, yythunkpos167= yythunkpos;  if (!yymatchChar('\'')) goto l167;  if (!yy_Sp()) goto l167;
  {  int yypos168= yypos, yythunkpos168= yythunkpos;  if (!yymatchChar(')')) goto l169;  goto l168;
  l169:;	  yypos= yypos168; yythunkpos= yythunkpos168;  if (!yy_Newline()) goto l167;
  }
  l168:;	  goto l166;
  l167:;	  yypos= yypos167; yythunkpos= yythunkpos167;
  }
  {  int yypos170= yypos, yythunkpos170= yythunkpos;  if (!yy_Newline()) goto l170;  goto l166;
  l170:;	  yypos= yypos170; yythunkpos= yythunkpos170;
  }  if (!yymatchDot()) goto l166;  goto l165;
  l166:;	  yypos= yypos166; yythunkpos= yythunkpos166;
  }  yyText(yybegin, yyend);  if (!(YY_END)) goto l164;  if (!yymatchChar('\'')) goto l164;
  yyprintf((stderr, "  ok   %s @ %s\n", "TitleSingle", yybuf+yypos));
  return 1;
  l164:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "TitleSingle", yybuf+yypos));
  return 0;
}

yy_OneStarClose()
{  int yypos0= yypos, yythunkpos0= yythunkpos;  yyDo(yyPush, 1, 0);
  yyprintf((stderr, "%s\n", "OneStarClose"));
  {  int yypos250= yypos, yythunkpos250= yythunkpos;  if (!yy_Spacechar()) goto l250;  goto l249;
  l250:;	  yypos= yypos250; yythunkpos= yythunkpos250;
  }
  {  int yypos251= yypos, yythunkpos251= yythunkpos;  if (!yy_Newline()) goto l251;  goto l249;
  l251:;	  yypos= yypos251; yythunkpos= yythunkpos251;
  }  if (!yy_Inline()) goto l249;  yyDo(yySet, -1, 0);
  {  int yypos252= yypos, yythunkpos252= yythunkpos;  if (!yy_StrongStar()) goto l252;  goto l249;
  l252:;	  yypos= yypos252; yythunkpos= yythunkpos252;
  }  if (!yymatchChar('*')) goto l249;  yyDo(yy_1_OneStarClose, yybegin, yyend);
  yyprintf((stderr, "  ok   %s @ %s\n", "OneStarClose", yybuf+yypos));  yyDo(yyPop, 1, 0);
  return 1;
  l249:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "OneStarClose", yybuf+yypos));
  return 0;
}

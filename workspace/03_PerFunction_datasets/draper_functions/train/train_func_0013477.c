yy_Doc()
{  int yypos0= yypos, yythunkpos0= yythunkpos;  yyDo(yyPush, 1, 0);
  yyprintf((stderr, "%s\n", "Doc"));
  {  int yypos1542= yypos, yythunkpos1542= yythunkpos;  if (!yy_BOM()) goto l1542;  goto l1543;
  l1542:;	  yypos= yypos1542; yythunkpos= yythunkpos1542;
  }
  l1543:;	  if (!yy_StartList()) goto l1541;  yyDo(yySet, -1, 0);
  l1544:;
  {  int yypos1545= yypos, yythunkpos1545= yythunkpos;  if (!yy_Block()) goto l1545;  yyDo(yy_1_Doc, yybegin, yyend);  goto l1544;
  l1545:;	  yypos= yypos1545; yythunkpos= yythunkpos1545;
  }  yyDo(yy_2_Doc, yybegin, yyend);
  yyprintf((stderr, "  ok   %s @ %s\n", "Doc", yybuf+yypos));  yyDo(yyPop, 1, 0);
  return 1;
  l1541:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "Doc", yybuf+yypos));
  return 0;
}

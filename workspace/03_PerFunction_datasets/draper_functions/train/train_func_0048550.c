yy_AtxInline()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "AtxInline"));
  {  int yypos1450= yypos, yythunkpos1450= yythunkpos;  if (!yy_Newline()) goto l1450;  goto l1449;
  l1450:;	  yypos= yypos1450; yythunkpos= yythunkpos1450;
  }
  {  int yypos1451= yypos, yythunkpos1451= yythunkpos;
  {  int yypos1452= yypos, yythunkpos1452= yythunkpos;  if (!yy_Sp()) goto l1452;  goto l1453;
  l1452:;	  yypos= yypos1452; yythunkpos= yythunkpos1452;
  }
  l1453:;
  l1454:;
  {  int yypos1455= yypos, yythunkpos1455= yythunkpos;  if (!yymatchChar('#')) goto l1455;  goto l1454;
  l1455:;	  yypos= yypos1455; yythunkpos= yythunkpos1455;
  }  if (!yy_Sp()) goto l1451;  if (!yy_Newline()) goto l1451;  goto l1449;
  l1451:;	  yypos= yypos1451; yythunkpos= yythunkpos1451;
  }  if (!yy_Inline()) goto l1449;
  yyprintf((stderr, "  ok   %s @ %s\n", "AtxInline", yybuf+yypos));
  return 1;
  l1449:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "AtxInline", yybuf+yypos));
  return 0;
}

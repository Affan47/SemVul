yy_SpecialChar()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "SpecialChar"));
  {  int yypos277= yypos, yythunkpos277= yythunkpos;  if (!yymatchChar('*')) goto l278;  goto l277;
  l278:;	  yypos= yypos277; yythunkpos= yythunkpos277;  if (!yymatchChar('_')) goto l279;  goto l277;
  l279:;	  yypos= yypos277; yythunkpos= yythunkpos277;  if (!yymatchChar('`')) goto l280;  goto l277;
  l280:;	  yypos= yypos277; yythunkpos= yythunkpos277;  if (!yymatchChar('&')) goto l281;  goto l277;
  l281:;	  yypos= yypos277; yythunkpos= yythunkpos277;  if (!yymatchChar('[')) goto l282;  goto l277;
  l282:;	  yypos= yypos277; yythunkpos= yythunkpos277;  if (!yymatchChar(']')) goto l283;  goto l277;
  l283:;	  yypos= yypos277; yythunkpos= yythunkpos277;  if (!yymatchChar('<')) goto l284;  goto l277;
  l284:;	  yypos= yypos277; yythunkpos= yythunkpos277;  if (!yymatchChar('!')) goto l285;  goto l277;
  l285:;	  yypos= yypos277; yythunkpos= yythunkpos277;  if (!yymatchChar('#')) goto l286;  goto l277;
  l286:;	  yypos= yypos277; yythunkpos= yythunkpos277;  if (!yymatchChar('\\')) goto l287;  goto l277;
  l287:;	  yypos= yypos277; yythunkpos= yythunkpos277;  if (!yy_ExtendedSpecialChar()) goto l276;
  }
  l277:;
  yyprintf((stderr, "  ok   %s @ %s\n", "SpecialChar", yybuf+yypos));
  return 1;
  l276:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "SpecialChar", yybuf+yypos));
  return 0;
}

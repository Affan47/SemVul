yy_Smart()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "Smart"));  yyText(yybegin, yyend);  if (!( extension(EXT_SMART) )) goto l322;
  {  int yypos323= yypos, yythunkpos323= yythunkpos;  if (!yy_Ellipsis()) goto l324;  goto l323;
  l324:;	  yypos= yypos323; yythunkpos= yythunkpos323;  if (!yy_Dash()) goto l325;  goto l323;
  l325:;	  yypos= yypos323; yythunkpos= yythunkpos323;  if (!yy_SingleQuoted()) goto l326;  goto l323;
  l326:;	  yypos= yypos323; yythunkpos= yythunkpos323;  if (!yy_DoubleQuoted()) goto l327;  goto l323;
  l327:;	  yypos= yypos323; yythunkpos= yythunkpos323;  if (!yy_Apostrophe()) goto l322;
  }
  l323:;
  yyprintf((stderr, "  ok   %s @ %s\n", "Smart", yybuf+yypos));
  return 1;
  l322:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "Smart", yybuf+yypos));
  return 0;
}

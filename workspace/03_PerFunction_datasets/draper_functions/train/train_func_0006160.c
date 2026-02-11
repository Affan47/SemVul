yy_grammar()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "grammar"));  if (!yy__()) goto l111;
  {  int yypos114= yypos, yythunkpos114= yythunkpos;  if (!yy_declaration()) goto l115;  goto l114;
  l115:;	  yypos= yypos114; yythunkpos= yythunkpos114;  if (!yy_definition()) goto l111;
  }
  l114:;
  l112:;
  {  int yypos113= yypos, yythunkpos113= yythunkpos;
  {  int yypos116= yypos, yythunkpos116= yythunkpos;  if (!yy_declaration()) goto l117;  goto l116;
  l117:;	  yypos= yypos116; yythunkpos= yythunkpos116;  if (!yy_definition()) goto l113;
  }
  l116:;	  goto l112;
  l113:;	  yypos= yypos113; yythunkpos= yythunkpos113;
  }
  {  int yypos118= yypos, yythunkpos118= yythunkpos;  if (!yy_trailer()) goto l118;  goto l119;
  l118:;	  yypos= yypos118; yythunkpos= yythunkpos118;
  }
  l119:;	  if (!yy_end_of_file()) goto l111;
  yyprintf((stderr, "  ok   %s @ %s\n", "grammar", yybuf+yypos));
  return 1;
  l111:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "grammar", yybuf+yypos));
  return 0;
}

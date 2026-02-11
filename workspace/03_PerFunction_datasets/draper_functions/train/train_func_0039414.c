yy_Note()
{  int yypos0= yypos, yythunkpos0= yythunkpos;  yyDo(yyPush, 2, 0);
  yyprintf((stderr, "%s\n", "Note"));  yyText(yybegin, yyend);  if (!( extension(EXT_NOTES) )) goto l1305;  if (!yy_NonindentSpace()) goto l1305;  if (!yy_RawNoteReference()) goto l1305;  yyDo(yySet, -2, 0);  if (!yymatchChar(':')) goto l1305;  if (!yy_Sp()) goto l1305;  if (!yy_StartList()) goto l1305;  yyDo(yySet, -1, 0);  if (!yy_RawNoteBlock()) goto l1305;  yyDo(yy_1_Note, yybegin, yyend);
  l1306:;
  {  int yypos1307= yypos, yythunkpos1307= yythunkpos;
  {  int yypos1308= yypos, yythunkpos1308= yythunkpos;  if (!yy_Indent()) goto l1307;  yypos= yypos1308; yythunkpos= yythunkpos1308;
  }  if (!yy_RawNoteBlock()) goto l1307;  yyDo(yy_2_Note, yybegin, yyend);  goto l1306;
  l1307:;	  yypos= yypos1307; yythunkpos= yythunkpos1307;
  }  yyDo(yy_3_Note, yybegin, yyend);
  yyprintf((stderr, "  ok   %s @ %s\n", "Note", yybuf+yypos));  yyDo(yyPop, 2, 0);
  return 1;
  l1305:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "Note", yybuf+yypos));
  return 0;
}

add_typedef_list_spec_string(pTHX_ SourcifyConfig *pSC, SV *str, TypedefList *pTDL)
{
  SV *s = newSVpv("typedef", 0);
  SourcifyState ss;

  CT_DEBUG(MAIN, (XSCLASS "::add_typedef_list_spec_string( pTDL=%p )", pTDL));

  ss.flags = F_KEYWORD;
  ss.pack  = 0;

  add_type_spec_string_rec(aTHX_ pSC, str, s, &pTDL->type, 0, &ss);

  if ((ss.flags & F_NEWLINE) == 0)
    sv_catpvn(s, " ", 1);

  add_typedef_list_decl_string(aTHX_ s, pTDL);

  sv_catpvn(s, ";\n", 2);

  if (ss.flags & F_PRAGMA_PACK_POP)
    sv_catpvn(s, "#pragma pack(pop)\n", 18);

  sv_catsv(str, s);

  SvREFCNT_dec(s);
}

def_union (definition *defp)
{
  token tok;
  declaration dec;
  case_list *cases;

  case_list **tailp;
#if 0
  int flag;
#endif

  defp->def_kind = DEF_UNION;
  scan (TOK_IDENT, &tok);
  defp->def_name = tok.str;
  scan (TOK_SWITCH, &tok);
  scan (TOK_LPAREN, &tok);
  get_declaration (&dec, DEF_UNION);
  defp->def.un.enum_decl = dec;
  tailp = &defp->def.un.cases;
  scan (TOK_RPAREN, &tok);
  scan (TOK_LBRACE, &tok);
  scan (TOK_CASE, &tok);
  while (tok.kind == TOK_CASE)
    {
      scan2 (TOK_IDENT, TOK_CHARCONST, &tok);
      cases = ALLOC (case_list);
      cases->case_name = tok.str;
      scan (TOK_COLON, &tok);

#if 0
      flag = 0;
#endif
      if (peekscan (TOK_CASE, &tok))
	{

	  do
	    {
	      scan2 (TOK_IDENT, TOK_CHARCONST, &tok);
	      cases->contflag = 1;
	      *tailp = cases;
	      tailp = &cases->next;
	      cases = ALLOC (case_list);
	      cases->case_name = tok.str;
	      scan (TOK_COLON, &tok);

	    }
	  while (peekscan (TOK_CASE, &tok));
	}
#if 0
      else if (flag)
	{

	  *tailp = cases;
	  tailp = &cases->next;
	  cases = ALLOC (case_list);
	};
#endif

      get_declaration (&dec, DEF_UNION);
      cases->case_decl = dec;
      cases->contflag = 0;
      *tailp = cases;
      tailp = &cases->next;
      scan (TOK_SEMICOLON, &tok);

      scan3 (TOK_CASE, TOK_DEFAULT, TOK_RBRACE, &tok);
    }
  *tailp = NULL;
  if (tok.kind == TOK_DEFAULT)
    {
      scan (TOK_COLON, &tok);
      get_declaration (&dec, DEF_UNION);
      defp->def.un.default_decl = ALLOC (declaration);
      *defp->def.un.default_decl = dec;
      scan (TOK_SEMICOLON, &tok);
      scan (TOK_RBRACE, &tok);
    }
  else
    {
      defp->def.un.default_decl = NULL;
    }
}

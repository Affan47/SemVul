symbol_clone (symbolS *orgsymP, int replace)
{
  symbolS *newsymP;
  asymbol *bsymorg, *bsymnew;


  gas_assert (orgsymP != &dot_symbol);


  if (LOCAL_SYMBOL_CHECK (orgsymP))
    orgsymP = local_symbol_convert ((struct local_symbol *) orgsymP);
  bsymorg = orgsymP->bsym;

  newsymP = (symbolS *) obstack_alloc (&notes, sizeof (*newsymP));
  *newsymP = *orgsymP;
  bsymnew = bfd_make_empty_symbol (bfd_asymbol_bfd (bsymorg));
  if (bsymnew == NULL)
    as_fatal ("bfd_make_empty_symbol: %s", bfd_errmsg (bfd_get_error ()));
  newsymP->bsym = bsymnew;
  bsymnew->name = bsymorg->name;
  bsymnew->flags = bsymorg->flags & ~BSF_SECTION_SYM;
  bsymnew->section = bsymorg->section;
  bfd_copy_private_symbol_data (bfd_asymbol_bfd (bsymorg), bsymorg,
				bfd_asymbol_bfd (bsymnew), bsymnew);

#ifdef obj_symbol_clone_hook
  obj_symbol_clone_hook (newsymP, orgsymP);
#endif

#ifdef tc_symbol_clone_hook
  tc_symbol_clone_hook (newsymP, orgsymP);
#endif

  if (replace)
    {
      if (symbol_rootP == orgsymP)
	symbol_rootP = newsymP;
      else if (orgsymP->sy_previous)
	{
	  orgsymP->sy_previous->sy_next = newsymP;
	  orgsymP->sy_previous = NULL;
	}
      if (symbol_lastP == orgsymP)
	symbol_lastP = newsymP;
      else if (orgsymP->sy_next)
	orgsymP->sy_next->sy_previous = newsymP;


      S_CLEAR_EXTERNAL (orgsymP);
      orgsymP->sy_previous = orgsymP->sy_next = orgsymP;
      debug_verify_symchain (symbol_rootP, symbol_lastP);

      symbol_table_insert (newsymP);
    }
  else
    {

      S_CLEAR_EXTERNAL (newsymP);
      newsymP->sy_previous = newsymP->sy_next = newsymP;
    }

  return newsymP;
}

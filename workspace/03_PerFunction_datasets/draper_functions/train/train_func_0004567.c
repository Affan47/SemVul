finish ()
{
  if (cur_scope && cur_scope->is(VAUL_TOP_SCOPE))
    pop_scope (cur_scope);

  if (eof)
    {
      release_ref (cur_du);
      cur_du = NULL;
    }

  if (cur_du && cur_du->get_tree ())
    {


      vaul_design_unit *u = cur_du->query_used_dus (NULL);
      pIIR_LibraryUnitList n = NULL, *nt = &n;
      while (u)
	{
	  *nt = mIIR_LibraryUnitList (-1, u->get_tree (), NULL);
	  nt = &(*nt)->rest;
	  u = cur_du->query_used_dus (u);
	}
      cur_du->get_tree()->used_units = n;
    }

  closing_label = NULL;
  cur_scope = NULL;

  decl_cache = NULL;
  tree_unprotect_loc ((tree_base_node **)&decl_cache);

  return cur_du;
}

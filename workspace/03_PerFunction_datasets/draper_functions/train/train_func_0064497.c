fname_decl (rid, id)
     unsigned rid;
     tree id;
{
  unsigned ix;
  tree decl = NULL_TREE;

  for (ix = 0; fname_vars[ix].decl; ix++)
    if (fname_vars[ix].rid == rid)
      break;

  decl = *fname_vars[ix].decl;
  if (!decl)
    {
      tree saved_last_tree = last_tree;


      int saved_lineno = lineno;
      lineno = 0;

      decl = (*make_fname_decl) (id, fname_vars[ix].pretty);
      if (last_tree != saved_last_tree)
	{


	  tree stmts = TREE_CHAIN (saved_last_tree);

	  TREE_CHAIN (saved_last_tree) = NULL_TREE;
	  last_tree = saved_last_tree;
	  saved_function_name_decls = tree_cons (decl, stmts,
						 saved_function_name_decls);
	}
      *fname_vars[ix].decl = decl;
      lineno = saved_lineno;
    }
  if (!ix && !current_function_decl)
    pedwarn_with_decl (decl, "`%s' is not defined outside of function scope");

  return decl;
}

instantiate_decls (tree fndecl)
{
  tree decl;
  unsigned ix;


  for (decl = DECL_ARGUMENTS (fndecl); decl; decl = DECL_CHAIN (decl))
    {
      instantiate_decl_rtl (DECL_RTL (decl));
      instantiate_decl_rtl (DECL_INCOMING_RTL (decl));
      if (DECL_HAS_VALUE_EXPR_P (decl))
	{
	  tree v = DECL_VALUE_EXPR (decl);
	  walk_tree (&v, instantiate_expr, NULL, NULL);
	}
    }

  if ((decl = DECL_RESULT (fndecl))
      && TREE_CODE (decl) == RESULT_DECL)
    {
      if (DECL_RTL_SET_P (decl))
	instantiate_decl_rtl (DECL_RTL (decl));
      if (DECL_HAS_VALUE_EXPR_P (decl))
	{
	  tree v = DECL_VALUE_EXPR (decl);
	  walk_tree (&v, instantiate_expr, NULL, NULL);
	}
    }


  instantiate_decls_1 (DECL_INITIAL (fndecl));

  FOR_EACH_LOCAL_DECL (cfun, ix, decl)
    if (DECL_RTL_SET_P (decl))
      instantiate_decl_rtl (DECL_RTL (decl));
  VEC_free (tree, gc, cfun->local_decls);
}

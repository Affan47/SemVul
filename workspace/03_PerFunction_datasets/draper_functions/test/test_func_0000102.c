instantiate_decls_1 (tree let)
{
  tree t;

  for (t = BLOCK_VARS (let); t; t = DECL_CHAIN (t))
    {
      if (DECL_RTL_SET_P (t))
	instantiate_decl_rtl (DECL_RTL (t));
      if (TREE_CODE (t) == VAR_DECL && DECL_HAS_VALUE_EXPR_P (t))
	{
	  tree v = DECL_VALUE_EXPR (t);
	  walk_tree (&v, instantiate_expr, NULL, NULL);
	}
    }


  for (t = BLOCK_SUBBLOCKS (let); t; t = BLOCK_CHAIN (t))
    instantiate_decls_1 (t);
}

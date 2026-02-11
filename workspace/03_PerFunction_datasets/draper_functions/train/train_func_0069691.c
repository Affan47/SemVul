uninitialized_vars_warning (tree block)
{
  tree decl, sub;
  for (decl = BLOCK_VARS (block); decl; decl = TREE_CHAIN (decl))
    {
      if (warn_uninitialized
	  && TREE_CODE (decl) == VAR_DECL


	  && ! AGGREGATE_TYPE_P (TREE_TYPE (decl))
	  && DECL_RTL_SET_P (decl)
	  && GET_CODE (DECL_RTL (decl)) == REG


	  && (DECL_INITIAL (decl) == NULL_TREE || lang_hooks.decl_uninit (decl))
	  && regno_uninitialized (REGNO (DECL_RTL (decl))))
	warning ("%J'%D' might be used uninitialized in this function",
		 decl, decl);
      if (extra_warnings
	  && TREE_CODE (decl) == VAR_DECL
	  && DECL_RTL_SET_P (decl)
	  && GET_CODE (DECL_RTL (decl)) == REG
	  && regno_clobbered_at_setjmp (REGNO (DECL_RTL (decl))))
	warning ("%Jvariable '%D' might be clobbered by `longjmp' or `vfork'",
		 decl, decl);
    }
  for (sub = BLOCK_SUBBLOCKS (block); sub; sub = TREE_CHAIN (sub))
    uninitialized_vars_warning (sub);
}

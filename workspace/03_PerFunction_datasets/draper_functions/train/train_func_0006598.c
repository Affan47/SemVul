at_function_scope_p (void)
{
  tree cs = current_scope ();


  return (cs && TREE_CODE (cs) == FUNCTION_DECL
	  && cfun && cfun->decl == current_function_decl);
}

outer_var_p (tree decl)
{
  return ((TREE_CODE (decl) == VAR_DECL || TREE_CODE (decl) == PARM_DECL)
	  && DECL_FUNCTION_SCOPE_P (decl)
	  && DECL_CONTEXT (decl) != current_function_decl);
}

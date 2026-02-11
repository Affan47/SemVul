get_fi_for_callee (gimple call)
{
  tree decl;


  decl = gimple_call_fndecl (call);
  if (decl)
    return get_vi_for_tree (decl);

  decl = gimple_call_fn (call);


  if (TREE_CODE (decl) == SSA_NAME)
    {
      if (TREE_CODE (decl) == SSA_NAME
	  && (TREE_CODE (SSA_NAME_VAR (decl)) == PARM_DECL
	      || TREE_CODE (SSA_NAME_VAR (decl)) == RESULT_DECL)
	  && SSA_NAME_IS_DEFAULT_DEF (decl))
	decl = SSA_NAME_VAR (decl);
      return get_vi_for_tree (decl);
    }
  else if (TREE_CODE (decl) == INTEGER_CST
	   || TREE_CODE (decl) == OBJ_TYPE_REF)
    return get_varinfo (anything_id);
  else
    gcc_unreachable ();
}

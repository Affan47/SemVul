get_fi_for_callee (gimple call)
{
  tree decl, fn = gimple_call_fn (call);

  if (fn && TREE_CODE (fn) == OBJ_TYPE_REF)
    fn = OBJ_TYPE_REF_EXPR (fn);


  decl = gimple_call_addr_fndecl (fn);
  if (decl)
    return get_vi_for_tree (decl);


  if (!fn || TREE_CODE (fn) != SSA_NAME)
    return get_varinfo (anything_id);

  if (SSA_NAME_IS_DEFAULT_DEF (fn)
      && (TREE_CODE (SSA_NAME_VAR (fn)) == PARM_DECL
	  || TREE_CODE (SSA_NAME_VAR (fn)) == RESULT_DECL))
    fn = SSA_NAME_VAR (fn);

  return get_vi_for_tree (fn);
}

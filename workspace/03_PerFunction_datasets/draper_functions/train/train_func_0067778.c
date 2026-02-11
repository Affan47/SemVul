lookup_name_current_level (tree name)
{
  tree decl = IDENTIFIER_SYMBOL_VALUE (name);

  if (decl == 0 || decl == error_mark_node || C_DECL_INVISIBLE (decl))
    return 0;

  if (current_scope == global_scope)
    return decl;


  if (TREE_CODE (decl) == PARM_DECL
      && chain_member (decl, current_scope->parms))
    return decl;
  if (chain_member (decl, current_scope->names))
    return decl;

  return 0;
}

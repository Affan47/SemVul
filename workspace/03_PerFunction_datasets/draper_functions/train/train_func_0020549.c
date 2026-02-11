i386_pe_binds_local_p (const_tree exp)
{
  if ((TREE_CODE (exp) == VAR_DECL || TREE_CODE (exp) == FUNCTION_DECL)
      && DECL_DLLIMPORT_P (exp))
    return false;


  if (DECL_P (exp)
      && !lookup_attribute ("weakref", DECL_ATTRIBUTES (exp))
      && TREE_PUBLIC (exp)
      && DECL_EXTERNAL (exp))
    return true;
  return default_binds_local_p_1 (exp, 0);
}

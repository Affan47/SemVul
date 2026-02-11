ref_may_alias_global_p (tree ref)
{
  tree base = get_base_address (ref);
  if (DECL_P (base))
    return is_global_var (base);
  else if (TREE_CODE (base) == MEM_REF
	   || TREE_CODE (base) == TARGET_MEM_REF)
    return ptr_deref_may_alias_global_p (TREE_OPERAND (base, 0));
  return true;
}

mem_ref_refers_to_non_mem_p (tree ref)
{
  tree base = TREE_OPERAND (ref, 0);
  if (TREE_CODE (base) != ADDR_EXPR)
    return false;
  base = TREE_OPERAND (base, 0);
  return (DECL_P (base)
	  && !TREE_ADDRESSABLE (base)
	  && DECL_MODE (base) != BLKmode
	  && DECL_RTL_SET_P (base)
	  && !MEM_P (DECL_RTL (base)));
}

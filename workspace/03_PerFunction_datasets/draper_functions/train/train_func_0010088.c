ptr_derefs_may_alias_p (tree ptr1, tree ptr2)
{
  struct ptr_info_def *pi1, *pi2;


  STRIP_NOPS (ptr1);
  STRIP_NOPS (ptr2);


  if (TREE_CODE (ptr1) == POINTER_PLUS_EXPR)
    {
      do
	{
	  ptr1 = TREE_OPERAND (ptr1, 0);
	}
      while (TREE_CODE (ptr1) == POINTER_PLUS_EXPR);
      return ptr_derefs_may_alias_p (ptr1, ptr2);
    }
  if (TREE_CODE (ptr2) == POINTER_PLUS_EXPR)
    {
      do
	{
	  ptr2 = TREE_OPERAND (ptr2, 0);
	}
      while (TREE_CODE (ptr2) == POINTER_PLUS_EXPR);
      return ptr_derefs_may_alias_p (ptr1, ptr2);
    }


  if (TREE_CODE (ptr1) == ADDR_EXPR)
    {
      tree base = get_base_address (TREE_OPERAND (ptr1, 0));
      if (base
	  && (TREE_CODE (base) == MEM_REF
	      || TREE_CODE (base) == TARGET_MEM_REF))
	return ptr_derefs_may_alias_p (TREE_OPERAND (base, 0), ptr2);
      else if (base
	       && DECL_P (base))
	return ptr_deref_may_alias_decl_p (ptr2, base);
      else
	return true;
    }
  if (TREE_CODE (ptr2) == ADDR_EXPR)
    {
      tree base = get_base_address (TREE_OPERAND (ptr2, 0));
      if (base
	  && (TREE_CODE (base) == MEM_REF
	      || TREE_CODE (base) == TARGET_MEM_REF))
	return ptr_derefs_may_alias_p (ptr1, TREE_OPERAND (base, 0));
      else if (base
	       && DECL_P (base))
	return ptr_deref_may_alias_decl_p (ptr1, base);
      else
	return true;
    }


  if (TREE_CODE (ptr1) != SSA_NAME
      || TREE_CODE (ptr2) != SSA_NAME
      || !POINTER_TYPE_P (TREE_TYPE (ptr1))
      || !POINTER_TYPE_P (TREE_TYPE (ptr2)))
    return true;


  if (ptr1 == ptr2)
    return true;


  pi1 = SSA_NAME_PTR_INFO (ptr1);
  pi2 = SSA_NAME_PTR_INFO (ptr2);
  if (!pi1 || !pi2)
    return true;


  return pt_solutions_intersect (&pi1->pt, &pi2->pt);
}

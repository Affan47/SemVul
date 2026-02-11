gimple_asm_clobbers_memory_p (const_gimple stmt)
{
  unsigned i;

  for (i = 0; i < gimple_asm_nclobbers (stmt); i++)
    {
      tree op = gimple_asm_clobber_op (stmt, i);
      if (strcmp (TREE_STRING_POINTER (TREE_VALUE (op)), "memory") == 0)
	return true;
    }

  return false;
}

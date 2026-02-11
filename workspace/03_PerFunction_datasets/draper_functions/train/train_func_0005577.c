verify_types_in_gimple_min_lval (tree expr)
{
  tree op;

  if (is_gimple_id (expr))
    return false;

  if (TREE_CODE (expr) != TARGET_MEM_REF
      && TREE_CODE (expr) != MEM_REF)
    {
      error ("invalid expression for min lvalue");
      return true;
    }


  if (TREE_CODE (expr) == TARGET_MEM_REF)
    return false;

  op = TREE_OPERAND (expr, 0);
  if (!is_gimple_val (op))
    {
      error ("invalid operand in indirect reference");
      debug_generic_stmt (op);
      return true;
    }


  return false;
}

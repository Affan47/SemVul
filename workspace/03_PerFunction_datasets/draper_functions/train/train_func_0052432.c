get_ancestor_addr_info (gimple assign, tree *obj_p, HOST_WIDE_INT *offset)
{
  HOST_WIDE_INT size, max_size;
  tree expr, parm, obj;

  if (!gimple_assign_single_p (assign))
    return NULL_TREE;
  expr = gimple_assign_rhs1 (assign);

  if (TREE_CODE (expr) != ADDR_EXPR)
    return NULL_TREE;
  expr = TREE_OPERAND (expr, 0);
  obj = expr;
  expr = get_ref_base_and_extent (expr, offset, &size, &max_size);

  if (TREE_CODE (expr) != MEM_REF

      || max_size == -1
      || max_size != size
      || *offset < 0)
    return NULL_TREE;
  parm = TREE_OPERAND (expr, 0);
  if (TREE_CODE (parm) != SSA_NAME
      || !SSA_NAME_IS_DEFAULT_DEF (parm)
      || TREE_CODE (SSA_NAME_VAR (parm)) != PARM_DECL)
    return NULL_TREE;

  *offset += mem_ref_offset (expr).low * BITS_PER_UNIT;
  *obj_p = obj;
  return expr;
}

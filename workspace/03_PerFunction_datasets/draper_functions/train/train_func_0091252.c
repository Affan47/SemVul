vn_reference_maybe_forwprop_address (VEC (vn_reference_op_s, heap) **ops,
				     unsigned int *i_p)
{
  unsigned int i = *i_p;
  vn_reference_op_t op = VEC_index (vn_reference_op_s, *ops, i);
  vn_reference_op_t mem_op = VEC_index (vn_reference_op_s, *ops, i - 1);
  gimple def_stmt;
  enum tree_code code;
  double_int off;

  def_stmt = SSA_NAME_DEF_STMT (op->op0);
  if (!is_gimple_assign (def_stmt))
    return;

  code = gimple_assign_rhs_code (def_stmt);
  if (code != ADDR_EXPR
      && code != POINTER_PLUS_EXPR)
    return;

  off = tree_to_double_int (mem_op->op0);
  off = double_int_sext (off, TYPE_PRECISION (TREE_TYPE (mem_op->op0)));


  if (code == ADDR_EXPR)
    {
      tree addr, addr_base;
      HOST_WIDE_INT addr_offset;

      addr = gimple_assign_rhs1 (def_stmt);
      addr_base = get_addr_base_and_unit_offset (TREE_OPERAND (addr, 0),
						 &addr_offset);
      if (!addr_base
	  || TREE_CODE (addr_base) != MEM_REF)
	return;

      off = double_int_add (off, shwi_to_double_int (addr_offset));
      off = double_int_add (off, mem_ref_offset (addr_base));
      op->op0 = TREE_OPERAND (addr_base, 0);
    }
  else
    {
      tree ptr, ptroff;
      ptr = gimple_assign_rhs1 (def_stmt);
      ptroff = gimple_assign_rhs2 (def_stmt);
      if (TREE_CODE (ptr) != SSA_NAME
	  || TREE_CODE (ptroff) != INTEGER_CST)
	return;

      off = double_int_add (off, tree_to_double_int (ptroff));
      op->op0 = ptr;
    }

  mem_op->op0 = double_int_to_tree (TREE_TYPE (mem_op->op0), off);
  if (host_integerp (mem_op->op0, 0))
    mem_op->off = TREE_INT_CST_LOW (mem_op->op0);
  else
    mem_op->off = -1;
  if (TREE_CODE (op->op0) == SSA_NAME)
    op->op0 = SSA_VAL (op->op0);
  if (TREE_CODE (op->op0) != SSA_NAME)
    op->opcode = TREE_CODE (op->op0);


  if (TREE_CODE (op->op0) == SSA_NAME)
    vn_reference_maybe_forwprop_address (ops, i_p);
  else if (TREE_CODE (op->op0) == ADDR_EXPR)
    vn_reference_fold_indirect (ops, i_p);
}

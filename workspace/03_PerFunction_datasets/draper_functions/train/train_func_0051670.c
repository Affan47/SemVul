stmt_local_def (gimple stmt)
{
  basic_block bb, def_bb;
  imm_use_iterator iter;
  use_operand_p use_p;
  tree val;
  def_operand_p def_p;

  if (gimple_has_side_effects (stmt)
      || gimple_vdef (stmt) != NULL_TREE
      || gimple_vuse (stmt) != NULL_TREE)
    return false;

  def_p = SINGLE_SSA_DEF_OPERAND (stmt, SSA_OP_DEF);
  if (def_p == NULL)
    return false;

  val = DEF_FROM_PTR (def_p);
  if (val == NULL_TREE || TREE_CODE (val) != SSA_NAME)
    return false;

  def_bb = gimple_bb (stmt);

  FOR_EACH_IMM_USE_FAST (use_p, iter, val)
    {
      if (is_gimple_debug (USE_STMT (use_p)))
	continue;
      bb = gimple_bb (USE_STMT (use_p));
      if (bb == def_bb)
	continue;

      if (gimple_code (USE_STMT (use_p)) == GIMPLE_PHI
	  && EDGE_PRED (bb, PHI_ARG_INDEX_FROM_USE (use_p))->src == def_bb)
	continue;

      return false;
    }

  return true;
}

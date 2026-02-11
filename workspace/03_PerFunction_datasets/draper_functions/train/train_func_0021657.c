reset_debug_uses (gimple stmt)
{
  ssa_op_iter op_iter;
  def_operand_p def_p;
  imm_use_iterator imm_iter;
  gimple use_stmt;

  if (!MAY_HAVE_DEBUG_STMTS)
    return;

  FOR_EACH_PHI_OR_STMT_DEF (def_p, stmt, op_iter, SSA_OP_DEF)
    {
      tree var = DEF_FROM_PTR (def_p);

      if (TREE_CODE (var) != SSA_NAME)
	continue;

      FOR_EACH_IMM_USE_STMT (use_stmt, imm_iter, var)
	{
	  if (!gimple_debug_bind_p (use_stmt))
	    continue;

	  gimple_debug_bind_reset_value (use_stmt);
	  update_stmt (use_stmt);
	}
    }
}

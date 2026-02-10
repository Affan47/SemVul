find_uses_to_rename_stmt (gimple stmt, bitmap *use_blocks, bitmap need_phis)
{
  ssa_op_iter iter;
  tree var;
  basic_block bb = gimple_bb (stmt);

  if (is_gimple_debug (stmt))
    return;

  FOR_EACH_SSA_TREE_OPERAND (var, stmt, iter, SSA_OP_ALL_USES)
    find_uses_to_rename_use (bb, var, use_blocks, need_phis);
}

mark_symbols_for_renaming (gimple stmt)
{
  tree op;
  ssa_op_iter iter;

  update_stmt (stmt);


  FOR_EACH_SSA_TREE_OPERAND (op, stmt, iter, SSA_OP_ALL_OPERANDS)
    if (DECL_P (op))
      mark_sym_for_renaming (op);
}

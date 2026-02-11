cond_arg_set_in_bb (edge e, basic_block bb)
{
  ssa_op_iter iter;
  use_operand_p use_p;
  gimple last = last_stmt (e->dest);


  if (!last)
    return false;

  if (gimple_code (last) != GIMPLE_COND
      && gimple_code (last) != GIMPLE_GOTO
      && gimple_code (last) != GIMPLE_SWITCH)
    return false;

  FOR_EACH_SSA_USE_OPERAND (use_p, last, iter, SSA_OP_USE | SSA_OP_VUSE)
    {
      tree use = USE_FROM_PTR (use_p);

      if (TREE_CODE (use) == SSA_NAME
	  && gimple_code (SSA_NAME_DEF_STMT (use)) != GIMPLE_PHI
	  && gimple_bb (SSA_NAME_DEF_STMT (use)) == bb)
	return true;
    }
  return false;
}

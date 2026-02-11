swap_tree_operands (gimple stmt, tree *exp0, tree *exp1)
{
  tree op0, op1;
  op0 = *exp0;
  op1 = *exp1;


  if (ssa_operands_active () && op0 != op1)
    {
      use_optype_p use0, use1, ptr;
      use0 = use1 = NULL;


      for (ptr = gimple_use_ops (stmt); ptr; ptr = ptr->next)
	if (USE_OP_PTR (ptr)->use == exp0)
	  {
	    use0 = ptr;
	    break;
	  }

      for (ptr = gimple_use_ops (stmt); ptr; ptr = ptr->next)
	if (USE_OP_PTR (ptr)->use == exp1)
	  {
	    use1 = ptr;
	    break;
	  }


      if (use0)
	USE_OP_PTR (use0)->use = exp1;
      if (use1)
	USE_OP_PTR (use1)->use = exp0;
    }


  *exp0 = op1;
  *exp1 = op0;
}

nearest_common_dominator_of_uses (gimple stmt, bool *debug_stmts)
{
  bitmap blocks = BITMAP_ALLOC (NULL);
  basic_block commondom;
  unsigned int j;
  bitmap_iterator bi;
  ssa_op_iter op_iter;
  imm_use_iterator imm_iter;
  use_operand_p use_p;
  tree var;

  bitmap_clear (blocks);
  FOR_EACH_SSA_TREE_OPERAND (var, stmt, op_iter, SSA_OP_ALL_DEFS)
    {
      FOR_EACH_IMM_USE_FAST (use_p, imm_iter, var)
        {
	  gimple usestmt = USE_STMT (use_p);
	  basic_block useblock;

	  if (gimple_code (usestmt) == GIMPLE_PHI)
	    {
	      int idx = PHI_ARG_INDEX_FROM_USE (use_p);

	      useblock = gimple_phi_arg_edge (usestmt, idx)->src;
	    }
	  else if (is_gimple_debug (usestmt))
	    {
	      *debug_stmts = true;
	      continue;
	    }
	  else
	    {
	      useblock = gimple_bb (usestmt);
	    }


	  if (useblock == ENTRY_BLOCK_PTR)
	    {
	      BITMAP_FREE (blocks);
	      return NULL;
	    }
	  bitmap_set_bit (blocks, useblock->index);
	}
    }
  commondom = BASIC_BLOCK (bitmap_first_set_bit (blocks));
  EXECUTE_IF_SET_IN_BITMAP (blocks, 0, j, bi)
    commondom = nearest_common_dominator (CDI_DOMINATORS, commondom,
					  BASIC_BLOCK (j));
  BITMAP_FREE (blocks);
  return commondom;
}

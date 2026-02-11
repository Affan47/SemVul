rewrite_debug_stmt_uses (gimple stmt)
{
  use_operand_p use_p;
  ssa_op_iter iter;
  bool update = false;

  FOR_EACH_SSA_USE_OPERAND (use_p, stmt, iter, SSA_OP_USE)
    {
      tree var = USE_FROM_PTR (use_p), def;
      common_info_p info = get_common_info (var);
      gcc_checking_assert (DECL_P (var));
      def = info->current_def;
      if (!def)
	{
	  if (TREE_CODE (var) == PARM_DECL && single_succ_p (ENTRY_BLOCK_PTR))
	    {
	      gimple_stmt_iterator gsi
		= gsi_after_labels (single_succ (ENTRY_BLOCK_PTR));
	      int lim;


	      for (lim = 32;
		   !gsi_end_p (gsi) && lim > 0;
		   gsi_next (&gsi), lim--)
		{
		  gimple gstmt = gsi_stmt (gsi);
		  if (!gimple_debug_source_bind_p (gstmt))
		    break;
		  if (gimple_debug_source_bind_get_value (gstmt) == var)
		    {
		      def = gimple_debug_source_bind_get_var (gstmt);
		      if (TREE_CODE (def) == DEBUG_EXPR_DECL)
			break;
		      else
			def = NULL_TREE;
		    }
		}

	      if (def == NULL_TREE)
		{
		  gimple def_temp;
		  def = make_node (DEBUG_EXPR_DECL);
		  def_temp = gimple_build_debug_source_bind (def, var, NULL);
		  DECL_ARTIFICIAL (def) = 1;
		  TREE_TYPE (def) = TREE_TYPE (var);
		  DECL_MODE (def) = DECL_MODE (var);
		  gsi = gsi_after_labels (single_succ (ENTRY_BLOCK_PTR));
		  gsi_insert_before (&gsi, def_temp, GSI_SAME_STMT);
		}
	      update = true;
	    }
	}
      else
	{

	  basic_block bb = gimple_bb (stmt);
	  basic_block def_bb
	      = SSA_NAME_IS_DEFAULT_DEF (def)
	      ? NULL : gimple_bb (SSA_NAME_DEF_STMT (def));


	  if (bb == def_bb)
	    ;


	  else if (def_bb && !dominated_by_p (CDI_DOMINATORS, bb, def_bb))
	    def = NULL;


	  else if (info->need_phi_state == NEED_PHI_STATE_NO)
	    ;
	  else
	    {
	      struct def_blocks_d *db_p = get_def_blocks_for (info);


	      if (bitmap_bit_p (db_p->livein_blocks, bb->index))
		;

	      else
		def = NULL;
	    }
	}
      if (def == NULL)
	{
	  gimple_debug_bind_reset_value (stmt);
	  update_stmt (stmt);
	  return;
	}
      SET_USE (use_p, def);
    }
  if (update)
    update_stmt (stmt);
}

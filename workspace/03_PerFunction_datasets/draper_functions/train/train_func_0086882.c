set_prologue_iterations (basic_block bb_before_first_loop,
			 tree *first_niters,
			 struct loop *loop,
			 unsigned int th)
{
  edge e;
  basic_block cond_bb, then_bb;
  tree var, prologue_after_cost_adjust_name;
  gimple_stmt_iterator gsi;
  gimple newphi;
  edge e_true, e_false, e_fallthru;
  gimple cond_stmt;
  gimple_seq gimplify_stmt_list = NULL, stmts = NULL;
  tree cost_pre_condition = NULL_TREE;
  tree scalar_loop_iters =
    unshare_expr (LOOP_VINFO_NITERS_UNCHANGED (loop_vec_info_for_loop (loop)));

  e = single_pred_edge (bb_before_first_loop);
  cond_bb = split_edge(e);

  e = single_pred_edge (bb_before_first_loop);
  then_bb = split_edge(e);
  set_immediate_dominator (CDI_DOMINATORS, then_bb, cond_bb);

  e_false = make_single_succ_edge (cond_bb, bb_before_first_loop,
				   EDGE_FALSE_VALUE);
  set_immediate_dominator (CDI_DOMINATORS, bb_before_first_loop, cond_bb);

  e_true = EDGE_PRED (then_bb, 0);
  e_true->flags &= ~EDGE_FALLTHRU;
  e_true->flags |= EDGE_TRUE_VALUE;

  e_fallthru = EDGE_SUCC (then_bb, 0);

  cost_pre_condition =
    fold_build2 (LE_EXPR, boolean_type_node, scalar_loop_iters,
	         build_int_cst (TREE_TYPE (scalar_loop_iters), th));
  cost_pre_condition =
    force_gimple_operand (cost_pre_condition, &gimplify_stmt_list,
			  true, NULL_TREE);
  cond_stmt = gimple_build_cond (NE_EXPR, cost_pre_condition,
				 build_int_cst (TREE_TYPE (cost_pre_condition),
						0), NULL_TREE, NULL_TREE);

  gsi = gsi_last_bb (cond_bb);
  if (gimplify_stmt_list)
    gsi_insert_seq_after (&gsi, gimplify_stmt_list, GSI_NEW_STMT);

  gsi = gsi_last_bb (cond_bb);
  gsi_insert_after (&gsi, cond_stmt, GSI_NEW_STMT);

  var = create_tmp_var (TREE_TYPE (scalar_loop_iters),
			"prologue_after_cost_adjust");
  add_referenced_var (var);
  prologue_after_cost_adjust_name =
    force_gimple_operand (scalar_loop_iters, &stmts, false, var);

  gsi = gsi_last_bb (then_bb);
  if (stmts)
    gsi_insert_seq_after (&gsi, stmts, GSI_NEW_STMT);

  newphi = create_phi_node (var, bb_before_first_loop);
  add_phi_arg (newphi, prologue_after_cost_adjust_name, e_fallthru,
	       UNKNOWN_LOCATION);
  add_phi_arg (newphi, *first_niters, e_false, UNKNOWN_LOCATION);

  *first_niters = PHI_RESULT (newphi);
}

set_prologue_iterations (basic_block bb_before_first_loop,
			 tree *first_niters,
			 struct loop *loop,
			 unsigned int th,
			 int probability)
{
  edge e;
  basic_block cond_bb, then_bb;
  tree var, prologue_after_cost_adjust_name;
  gimple_stmt_iterator gsi;
  gimple newphi;
  edge e_true, e_false, e_fallthru;
  gimple cond_stmt;
  gimple_seq stmts = NULL;
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

  e_true->probability = probability;
  e_false->probability = inverse_probability (probability);
  e_true->count = apply_probability (cond_bb->count, probability);
  e_false->count = cond_bb->count - e_true->count;
  then_bb->frequency = EDGE_FREQUENCY (e_true);
  then_bb->count = e_true->count;

  e_fallthru = EDGE_SUCC (then_bb, 0);
  e_fallthru->count = then_bb->count;

  gsi = gsi_last_bb (cond_bb);
  cost_pre_condition =
    fold_build2 (LE_EXPR, boolean_type_node, scalar_loop_iters,
	         build_int_cst (TREE_TYPE (scalar_loop_iters), th));
  cost_pre_condition =
    force_gimple_operand_gsi_1 (&gsi, cost_pre_condition, is_gimple_condexpr,
				NULL_TREE, false, GSI_CONTINUE_LINKING);
  cond_stmt = gimple_build_cond_from_tree (cost_pre_condition,
					   NULL_TREE, NULL_TREE);
  gsi_insert_after (&gsi, cond_stmt, GSI_NEW_STMT);

  var = create_tmp_var (TREE_TYPE (scalar_loop_iters),
			"prologue_after_cost_adjust");
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

vect_detect_hybrid_slp_stmts (slp_tree node)
{
  int i;
  VEC (gimple, heap) *stmts = SLP_TREE_SCALAR_STMTS (node);
  gimple stmt = VEC_index (gimple, stmts, 0);
  imm_use_iterator imm_iter;
  gimple use_stmt;
  stmt_vec_info stmt_vinfo = vinfo_for_stmt (stmt);
  slp_void_p child;
  loop_vec_info loop_vinfo = STMT_VINFO_LOOP_VINFO (stmt_vinfo);
  struct loop *loop = NULL;
  bb_vec_info bb_vinfo = STMT_VINFO_BB_VINFO (stmt_vinfo);
  basic_block bb = NULL;

  if (!node)
    return;

  if (loop_vinfo)
    loop = LOOP_VINFO_LOOP (loop_vinfo);
  else
    bb = BB_VINFO_BB (bb_vinfo);

  FOR_EACH_VEC_ELT (gimple, SLP_TREE_SCALAR_STMTS (node), i, stmt)
    if (PURE_SLP_STMT (vinfo_for_stmt (stmt))
	&& TREE_CODE (gimple_op (stmt, 0)) == SSA_NAME)
      FOR_EACH_IMM_USE_STMT (use_stmt, imm_iter, gimple_op (stmt, 0))
	if (gimple_bb (use_stmt)
            && ((loop && flow_bb_inside_loop_p (loop, gimple_bb (use_stmt)))
		 || bb == gimple_bb (use_stmt))
	    && (stmt_vinfo = vinfo_for_stmt (use_stmt))
	    && !STMT_SLP_TYPE (stmt_vinfo)
            && (STMT_VINFO_RELEVANT (stmt_vinfo)
                || VECTORIZABLE_CYCLE_DEF (STMT_VINFO_DEF_TYPE (stmt_vinfo)))
	    && !(gimple_code (use_stmt) == GIMPLE_PHI
                 && STMT_VINFO_DEF_TYPE (stmt_vinfo)
                  == vect_reduction_def))
	  vect_mark_slp_stmts (node, hybrid, i);

  FOR_EACH_VEC_ELT (slp_void_p, SLP_TREE_CHILDREN (node), i, child)
    vect_detect_hybrid_slp_stmts ((slp_tree) child);
}

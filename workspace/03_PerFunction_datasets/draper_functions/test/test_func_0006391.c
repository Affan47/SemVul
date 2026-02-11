tree_estimate_probability_bb (basic_block bb)
{
  edge e;
  edge_iterator ei;
  gimple last;

  FOR_EACH_EDGE (e, ei, bb->succs)
    {

      if (e->dest != EXIT_BLOCK_PTR)
	{
	  gimple_stmt_iterator gi;
	  for (gi = gsi_start_bb (e->dest); !gsi_end_p (gi); gsi_next (&gi))
	    {
	      gimple stmt = gsi_stmt (gi);
	      tree decl;

	      if (gimple_code (stmt) != GIMPLE_LABEL)
		break;
	      decl = gimple_label_label (stmt);
	      if (DECL_ARTIFICIAL (decl))
		continue;


	      if (lookup_attribute ("cold", DECL_ATTRIBUTES (decl)))
		predict_edge_def (e, PRED_COLD_LABEL, NOT_TAKEN);
	      else if (lookup_attribute ("hot", DECL_ATTRIBUTES (decl)))
		predict_edge_def (e, PRED_HOT_LABEL, TAKEN);
	    }
	}


      if (e->dest != bb->next_bb
	  && e->dest != EXIT_BLOCK_PTR
	  && single_succ_p (e->dest)
	  && single_succ_edge (e->dest)->dest == EXIT_BLOCK_PTR
	  && (last = last_stmt (e->dest)) != NULL
	  && gimple_code (last) == GIMPLE_RETURN)
	{
	  edge e1;
	  edge_iterator ei1;

	  if (single_succ_p (bb))
	    {
	      FOR_EACH_EDGE (e1, ei1, bb->preds)
		if (!predicted_by_p (e1->src, PRED_NULL_RETURN)
		    && !predicted_by_p (e1->src, PRED_CONST_RETURN)
		    && !predicted_by_p (e1->src, PRED_NEGATIVE_RETURN))
		  predict_edge_def (e1, PRED_TREE_EARLY_RETURN, NOT_TAKEN);
	    }
	  else
	    if (!predicted_by_p (e->src, PRED_NULL_RETURN)
		&& !predicted_by_p (e->src, PRED_CONST_RETURN)
		&& !predicted_by_p (e->src, PRED_NEGATIVE_RETURN))
	      predict_edge_def (e, PRED_TREE_EARLY_RETURN, NOT_TAKEN);
	}


      if (e->dest != EXIT_BLOCK_PTR && e->dest != bb
	  && dominated_by_p (CDI_DOMINATORS, e->dest, e->src)
	  && !dominated_by_p (CDI_POST_DOMINATORS, e->src, e->dest))
	{
	  gimple_stmt_iterator bi;


	  for (bi = gsi_start_bb (e->dest); !gsi_end_p (bi);
	       gsi_next (&bi))
	    {
	      gimple stmt = gsi_stmt (bi);
	      if (is_gimple_call (stmt)


		  && gimple_has_side_effects (stmt))
		{
		  predict_edge_def (e, PRED_CALL, NOT_TAKEN);
		  break;
		}
	    }
	}
    }
  tree_predict_by_opcode (bb);
}

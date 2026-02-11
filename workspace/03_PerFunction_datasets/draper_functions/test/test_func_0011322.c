genericize_cp_loop (tree *stmt_p, location_t start_locus, tree cond, tree body,
		    tree incr, bool cond_is_first, int *walk_subtrees,
		    void *data)
{
  tree blab, clab;
  tree entry = NULL, exit = NULL, t;
  tree stmt_list = NULL;

  blab = begin_bc_block (bc_break, start_locus);
  clab = begin_bc_block (bc_continue, start_locus);

  if (incr && EXPR_P (incr))
    SET_EXPR_LOCATION (incr, start_locus);

  cp_walk_tree (&cond, cp_genericize_r, data, NULL);
  cp_walk_tree (&body, cp_genericize_r, data, NULL);
  cp_walk_tree (&incr, cp_genericize_r, data, NULL);
  *walk_subtrees = 0;


  if (cond && integer_zerop (cond))
    {
      if (cond_is_first)
	{
	  t = build1_loc (start_locus, GOTO_EXPR, void_type_node,
			  get_bc_label (bc_break));
	  append_to_statement_list (t, &stmt_list);
	}
    }
  else
    {

      tree top = build1 (LABEL_EXPR, void_type_node,
			 create_artificial_label (start_locus));


      exit = build1 (GOTO_EXPR, void_type_node, LABEL_EXPR_LABEL (top));

      if (cond && !integer_nonzerop (cond))
	{


	  if (cond_is_first)
	    {
	      if (incr)
		{
		  entry = build1 (LABEL_EXPR, void_type_node,
				  create_artificial_label (start_locus));
		  t = build1_loc (start_locus, GOTO_EXPR, void_type_node,
				  LABEL_EXPR_LABEL (entry));
		}
	      else
		t = build1_loc (start_locus, GOTO_EXPR, void_type_node,
				get_bc_label (bc_continue));
	      append_to_statement_list (t, &stmt_list);
	    }

	  t = build1 (GOTO_EXPR, void_type_node, get_bc_label (bc_break));
	  exit = fold_build3_loc (start_locus,
				  COND_EXPR, void_type_node, cond, exit, t);
	}

      append_to_statement_list (top, &stmt_list);
    }

  append_to_statement_list (body, &stmt_list);
  finish_bc_block (&stmt_list, bc_continue, clab);
  append_to_statement_list (incr, &stmt_list);
  append_to_statement_list (entry, &stmt_list);
  append_to_statement_list (exit, &stmt_list);
  finish_bc_block (&stmt_list, bc_break, blab);

  if (stmt_list == NULL_TREE)
    stmt_list = build1 (NOP_EXPR, void_type_node, integer_zero_node);

  *stmt_p = stmt_list;
}

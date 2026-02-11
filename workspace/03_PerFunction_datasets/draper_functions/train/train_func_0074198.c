expr_reaches_here_p_work (occr, expr, bb, check_self_loop, visited)
     struct occr *occr;
     struct expr *expr;
     basic_block bb;
     int check_self_loop;
     char *visited;
{
  edge pred;

  for (pred = bb->pred; pred != NULL; pred = pred->pred_next)
    {
      basic_block pred_bb = pred->src;

      if (visited[pred_bb->index])

	  ;
      else if (pred_bb == bb)
	{

	  if (check_self_loop
	      && TEST_BIT (ae_gen[pred_bb->index], expr->bitmap_index)
	      && BLOCK_NUM (occr->insn) == pred_bb->index)
	    return 1;

	  visited[pred_bb->index] = 1;
	}


      else if (TEST_BIT (ae_kill[pred_bb->index], expr->bitmap_index))
	visited[pred_bb->index] = 1;


      else if (TEST_BIT (ae_gen[pred_bb->index], expr->bitmap_index))
	{


	  if (BLOCK_NUM (occr->insn) == pred_bb->index)
	    return 1;

	  visited[pred_bb->index] = 1;
	}


      else
	{
	  visited[pred_bb->index] = 1;
	  if (expr_reaches_here_p_work (occr, expr, pred_bb, check_self_loop,
	      visited))

	    return 1;
	}
    }


  return 0;
}

copy_bbs (basic_block *bbs, unsigned n, basic_block *new_bbs,
	  edge *edges, unsigned n_edges, edge *new_edges,
	  struct loop *base)
{
  unsigned i, j;
  basic_block bb, new_bb, dom_bb;
  edge e;


  for (i = 0; i < n; i++)
    {

      bb = bbs[i];
      new_bb = new_bbs[i] = cfg_layout_duplicate_bb (bb, NULL);
      bb->rbi->duplicated = 1;

      add_bb_to_loop (new_bb, bb->loop_father->copy);
      add_to_dominance_info (CDI_DOMINATORS, new_bb);

      if (bb->loop_father->header == bb && bb->loop_father != base)
	new_bb->loop_father->header = new_bb;

      if (bb->loop_father->latch == bb && bb->loop_father != base)
	new_bb->loop_father->latch = new_bb;
    }


  for (i = 0; i < n; i++)
    {
      bb = bbs[i];
      new_bb = new_bbs[i];

      dom_bb = get_immediate_dominator (CDI_DOMINATORS, bb);
      if (dom_bb->rbi->duplicated)
	{
	  dom_bb = dom_bb->rbi->copy;
	  set_immediate_dominator (CDI_DOMINATORS, new_bb, dom_bb);
	}
    }


  for (j = 0; j < n_edges; j++)
    new_edges[j] = NULL;
  for (i = 0; i < n; i++)
    {
      new_bb = new_bbs[i];
      bb = bbs[i];

      for (e = new_bb->succ; e; e = e->succ_next)
	{
	  for (j = 0; j < n_edges; j++)
	    if (edges[j] && edges[j]->src == bb && edges[j]->dest == e->dest)
	      new_edges[j] = e;

	  if (!e->dest->rbi->duplicated)
	    continue;
	  redirect_edge_and_branch_force (e, e->dest->rbi->copy);
	}
    }


  for (i = 0; i < n; i++)
    bbs[i]->rbi->duplicated = 0;
}

order_nodes_in_scc (ddg_ptr g, sbitmap nodes_ordered, sbitmap scc,
		    int * node_order, int pos)
{
  enum sms_direction dir;
  int num_nodes = g->num_nodes;
  sbitmap workset = sbitmap_alloc (num_nodes);
  sbitmap tmp = sbitmap_alloc (num_nodes);
  sbitmap zero_bitmap = sbitmap_alloc (num_nodes);
  sbitmap predecessors = sbitmap_alloc (num_nodes);
  sbitmap successors = sbitmap_alloc (num_nodes);

  bitmap_clear (predecessors);
  find_predecessors (predecessors, g, nodes_ordered);

  bitmap_clear (successors);
  find_successors (successors, g, nodes_ordered);

  bitmap_clear (tmp);
  if (bitmap_and (tmp, predecessors, scc))
    {
      bitmap_copy (workset, tmp);
      dir = BOTTOMUP;
    }
  else if (bitmap_and (tmp, successors, scc))
    {
      bitmap_copy (workset, tmp);
      dir = TOPDOWN;
    }
  else
    {
      int u;

      bitmap_clear (workset);
      if ((u = find_max_asap (g, scc)) >= 0)
	bitmap_set_bit (workset, u);
      dir = BOTTOMUP;
    }

  bitmap_clear (zero_bitmap);
  while (!bitmap_equal_p (workset, zero_bitmap))
    {
      int v;
      ddg_node_ptr v_node;
      sbitmap v_node_preds;
      sbitmap v_node_succs;

      if (dir == TOPDOWN)
	{
	  while (!bitmap_equal_p (workset, zero_bitmap))
	    {
	      v = find_max_hv_min_mob (g, workset);
	      v_node = &g->nodes[v];
	      node_order[pos++] = v;
	      v_node_succs = NODE_SUCCESSORS (v_node);
	      bitmap_and (tmp, v_node_succs, scc);


	      bitmap_and_compl (tmp, tmp, nodes_ordered);
	      bitmap_ior (workset, workset, tmp);
	      bitmap_clear_bit (workset, v);
	      bitmap_set_bit (nodes_ordered, v);
	    }
	  dir = BOTTOMUP;
	  bitmap_clear (predecessors);
	  find_predecessors (predecessors, g, nodes_ordered);
	  bitmap_and (workset, predecessors, scc);
	}
      else
	{
	  while (!bitmap_equal_p (workset, zero_bitmap))
	    {
	      v = find_max_dv_min_mob (g, workset);
	      v_node = &g->nodes[v];
	      node_order[pos++] = v;
	      v_node_preds = NODE_PREDECESSORS (v_node);
	      bitmap_and (tmp, v_node_preds, scc);


	      bitmap_and_compl (tmp, tmp, nodes_ordered);
	      bitmap_ior (workset, workset, tmp);
	      bitmap_clear_bit (workset, v);
	      bitmap_set_bit (nodes_ordered, v);
	    }
	  dir = TOPDOWN;
	  bitmap_clear (successors);
	  find_successors (successors, g, nodes_ordered);
	  bitmap_and (workset, successors, scc);
	}
    }
  sbitmap_free (tmp);
  sbitmap_free (workset);
  sbitmap_free (zero_bitmap);
  sbitmap_free (predecessors);
  sbitmap_free (successors);
  return pos;
}

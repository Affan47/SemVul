compute_nearerout (struct edge_list *edge_list, sbitmap *farthest,
		   sbitmap *st_avloc, sbitmap *nearer, sbitmap *nearerout)
{
  int num_edges, i;
  edge e;
  basic_block *worklist, *tos, bb;
  edge_iterator ei;

  num_edges = NUM_EDGES (edge_list);


  tos = worklist = XNEWVEC (basic_block, n_basic_blocks + 1);


  for (i = 0; i < num_edges; i++)
    INDEX_EDGE (edge_list, i)->aux = (void *) (size_t) i;


  bitmap_vector_ones (nearer, num_edges);


  FOR_EACH_EDGE (e, ei, EXIT_BLOCK_PTR->preds)
    bitmap_copy (nearer[(size_t)e->aux], farthest[(size_t)e->aux]);


  FOR_EACH_BB (bb)
    {
      *tos++ = bb;
      bb->aux = bb;
    }


  while (tos != worklist)
    {

      bb = *--tos;
      bb->aux = NULL;


      bitmap_ones (nearerout[bb->index]);
      FOR_EACH_EDGE (e, ei, bb->succs)
	bitmap_and (nearerout[bb->index], nearerout[bb->index],
			 nearer[(size_t) e->aux]);


      FOR_EACH_EDGE (e, ei, bb->preds)
	if (bitmap_ior_and_compl (nearer[(size_t) e->aux],
				      farthest[(size_t) e->aux],
				      nearerout[e->dest->index],
				      st_avloc[e->dest->index])


	    && e->src != ENTRY_BLOCK_PTR && e->src->aux == 0)
	  {
	    *tos++ = e->src;
	    e->src->aux = e;
	  }
    }


  bitmap_ones (nearerout[last_basic_block]);
  FOR_EACH_EDGE (e, ei, ENTRY_BLOCK_PTR->succs)
    bitmap_and (nearerout[last_basic_block],
		     nearerout[last_basic_block],
		     nearer[(size_t) e->aux]);

  clear_aux_for_edges ();
  free (tos);
}

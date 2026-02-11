compute_laterin (edge_list, earliest, antloc, later, laterin)
     struct edge_list *edge_list;
     sbitmap *earliest, *antloc, *later, *laterin;
{
  int num_edges, i;
  edge e;
  basic_block *worklist, *qin, *qout, *qend, bb;
  unsigned int qlen;

  num_edges = NUM_EDGES (edge_list);


  qin = qout = worklist
    = (basic_block *) xmalloc (sizeof (basic_block) * (n_basic_blocks + 1));


  for (i = 0; i < num_edges; i++)
    INDEX_EDGE (edge_list, i)->aux = (void *) (size_t) i;


  sbitmap_vector_ones (later, num_edges);


  for (e = ENTRY_BLOCK_PTR->succ; e; e = e->succ_next)
    sbitmap_copy (later[(size_t) e->aux], earliest[(size_t) e->aux]);


  FOR_EACH_BB (bb)
    {
      *qin++ = bb;
      bb->aux = bb;
    }
  qin = worklist;


  qend = &worklist[n_basic_blocks];
  qlen = n_basic_blocks;


  while (qlen)
    {

      bb = *qout++;
      bb->aux = NULL;
      qlen--;
      if (qout >= qend)
	qout = worklist;


      sbitmap_ones (laterin[bb->index]);
      for (e = bb->pred; e != NULL; e = e->pred_next)
	sbitmap_a_and_b (laterin[bb->index], laterin[bb->index], later[(size_t)e->aux]);


      for (e = bb->succ; e != NULL; e = e->succ_next)
	if (sbitmap_union_of_diff_cg (later[(size_t) e->aux],
				      earliest[(size_t) e->aux],
				      laterin[e->src->index],
				      antloc[e->src->index])


	    && e->dest != EXIT_BLOCK_PTR && e->dest->aux == 0)
	  {
	    *qin++ = e->dest;
	    e->dest->aux = e;
	    qlen++;
	    if (qin >= qend)
	      qin = worklist;
	  }
    }


  sbitmap_ones (laterin[last_basic_block]);
  for (e = EXIT_BLOCK_PTR->pred; e != NULL; e = e->pred_next)
    sbitmap_a_and_b (laterin[last_basic_block],
		     laterin[last_basic_block],
		     later[(size_t) e->aux]);

  clear_aux_for_edges ();
  free (worklist);
}

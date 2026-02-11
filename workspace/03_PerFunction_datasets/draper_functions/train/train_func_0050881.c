_dxfBuildEdgeHeap(SimpData *simp_data)
{

  int
    can_add_edge  = 1,
    n_edges_added = 0,
    nE            = simp_data->nE;

  while (can_add_edge && simp_data->last_edge_added2heap < nE)
    {
      if ( simp_data->edge2index[simp_data->last_edge_added2heap]  ==
	   simp_data->heap_initial_index )


	n_edges_added +=
	  (can_add_edge =
	   simp_data->add_edge(simp_data, simp_data->last_edge_added2heap));


      simp_data->last_edge_added2heap ++;

    }

  return (n_edges_added);
}

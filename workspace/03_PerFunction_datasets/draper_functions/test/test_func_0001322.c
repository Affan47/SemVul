elim_graph_remove_succ_edge (elim_graph g, int node, source_location *locus)
{
  int y;
  unsigned x;
  for (x = 0; x < g->edge_list.length (); x += 2)
    if (g->edge_list[x] == node)
      {
        g->edge_list[x] = -1;
	y = g->edge_list[x + 1];
	g->edge_list[x + 1] = -1;
	*locus = g->edge_locus[x / 2];
	g->edge_locus[x / 2] = UNKNOWN_LOCATION;
	return y;
      }
  *locus = UNKNOWN_LOCATION;
  return -1;
}

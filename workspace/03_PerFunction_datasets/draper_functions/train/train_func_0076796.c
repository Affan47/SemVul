update_edge_key (fibheap_t heap, struct cgraph_edge *edge)
{
  int badness = cgraph_edge_badness (edge, false);
  if (edge->aux)
    {
      fibnode_t n = (fibnode_t) edge->aux;
      gcc_checking_assert (n->data == edge);


      if (badness < n->key)
	{
	  fibheap_replace_key (heap, n, badness);
	  gcc_checking_assert (n->key == badness);
	}
    }
  else
    edge->aux = fibheap_insert (heap, badness, edge);
}

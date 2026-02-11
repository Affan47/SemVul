loop_with_complex_edge_p (struct loop *loop)
{
  int i;
  edge_iterator ei;
  edge e;
  VEC (edge, heap) *edges;
  bool res;

  FOR_EACH_EDGE (e, ei, loop->header->preds)
    if (e->flags & EDGE_EH)
      return true;
  edges = get_loop_exit_edges (loop);
  res = false;
  FOR_EACH_VEC_ELT (edge, edges, i, e)
    if (e->flags & EDGE_COMPLEX)
      {
	res = true;
	break;
      }
  VEC_free (edge, heap, edges);
  return res;
}

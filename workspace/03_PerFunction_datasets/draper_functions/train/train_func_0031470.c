loop_with_complex_edge_p (struct loop *loop)
{
  int i;
  edge_iterator ei;
  edge e;
  vec<edge> edges;
  bool res;

  FOR_EACH_EDGE (e, ei, loop->header->preds)
    if (e->flags & EDGE_EH)
      return true;
  edges = get_loop_exit_edges (loop);
  res = false;
  FOR_EACH_VEC_ELT (edges, i, e)
    if (e->flags & EDGE_COMPLEX)
      {
	res = true;
	break;
      }
  edges.release ();
  return res;
}

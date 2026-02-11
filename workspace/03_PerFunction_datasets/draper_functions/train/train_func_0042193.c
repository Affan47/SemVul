find_loop_niter_by_eval (struct loop *loop, edge *exit)
{
  unsigned i;
  VEC (edge, heap) *exits = get_loop_exit_edges (loop);
  edge ex;
  tree niter = NULL_TREE, aniter;

  *exit = NULL;


  if (!flag_expensive_optimizations
      && VEC_length (edge, exits) > 1)
    return chrec_dont_know;

  FOR_EACH_VEC_ELT (edge, exits, i, ex)
    {
      if (!just_once_each_iteration_p (loop, ex->src))
	continue;

      aniter = loop_niter_by_eval (loop, ex);
      if (chrec_contains_undetermined (aniter))
	continue;

      if (niter
	  && !tree_int_cst_lt (aniter, niter))
	continue;

      niter = aniter;
      *exit = ex;
    }
  VEC_free (edge, heap, exits);

  return niter ? niter : chrec_dont_know;
}

estimate_numbers_of_iterations_loop (struct loop *loop, bool use_undefined_p)
{
  VEC (edge, heap) *exits;
  tree niter, type;
  unsigned i;
  struct tree_niter_desc niter_desc;
  edge ex;
  double_int bound;


  if (loop->estimate_state != EST_NOT_COMPUTED)
    return;
  loop->estimate_state = EST_AVAILABLE;
  loop->any_upper_bound = false;
  loop->any_estimate = false;

  exits = get_loop_exit_edges (loop);
  FOR_EACH_VEC_ELT (edge, exits, i, ex)
    {
      if (!number_of_iterations_exit (loop, ex, &niter_desc, false))
	continue;

      niter = niter_desc.niter;
      type = TREE_TYPE (niter);
      if (TREE_CODE (niter_desc.may_be_zero) != INTEGER_CST)
	niter = build3 (COND_EXPR, type, niter_desc.may_be_zero,
			build_int_cst (type, 0),
			niter);
      record_estimate (loop, niter, niter_desc.max,
		       last_stmt (ex->src),
		       true, true, true);
    }
  VEC_free (edge, heap, exits);

  if (use_undefined_p)
    infer_loop_bounds_from_undefined (loop);


  if (loop->header->count != 0)
    {
      gcov_type nit = expected_loop_iterations_unbounded (loop) + 1;
      bound = gcov_type_to_double_int (nit);
      record_niter_bound (loop, bound, true, false);
    }


  if (loop->any_upper_bound
      && loop->any_estimate
      && double_int_ucmp (loop->nb_iterations_upper_bound,
			  loop->nb_iterations_estimate) < 0)
    loop->nb_iterations_estimate = loop->nb_iterations_upper_bound;
}

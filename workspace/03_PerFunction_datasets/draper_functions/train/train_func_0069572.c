collect_condition_stmts (struct loop *loop, VEC (gimple, heap) **conds)
{
  unsigned i;
  edge e;
  VEC (edge, heap) *exits = get_loop_exit_edges (loop);

  FOR_EACH_VEC_ELT (edge, exits, i, e)
    {
      gimple cond = last_stmt (e->src);

      if (cond)
	VEC_safe_push (gimple, heap, *conds, cond);
    }

  VEC_free (edge, heap, exits);
}

build_rdg (struct loop *loop,
	   VEC (loop_p, heap) **loop_nest,
	   VEC (ddr_p, heap) **dependence_relations,
	   VEC (data_reference_p, heap) **datarefs)
{
  struct graph *rdg = NULL;
  VEC (gimple, heap) *stmts = VEC_alloc (gimple, heap, 10);

  compute_data_dependences_for_loop (loop, false, loop_nest, datarefs,
				     dependence_relations);

  if (known_dependences_p (*dependence_relations))
    {
      stmts_from_loop (loop, &stmts);
      rdg = build_empty_rdg (VEC_length (gimple, stmts));
      create_rdg_vertices (rdg, stmts);
      create_rdg_edges (rdg, *dependence_relations);
    }

  VEC_free (gimple, heap, stmts);
  return rdg;
}

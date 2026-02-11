distribute_loop (struct loop *loop, vec<gimple> stmts)
{
  int res = 0;
  struct graph *rdg;
  gimple s;
  unsigned i;
  vec<int> vertices;
  vec<ddr_p> dependence_relations;
  vec<data_reference_p> datarefs;
  vec<loop_p> loop_nest;

  datarefs.create (10);
  dependence_relations.create (100);
  loop_nest.create (3);
  rdg = build_rdg (loop, &loop_nest, &dependence_relations, &datarefs);

  if (!rdg)
    {
      if (dump_file && (dump_flags & TDF_DETAILS))
	fprintf (dump_file,
		 "FIXME: Loop %d not distributed: failed to build the RDG.\n",
		 loop->num);

      free_dependence_relations (dependence_relations);
      free_data_refs (datarefs);
      loop_nest.release ();
      return res;
    }

  vertices.create (3);

  if (dump_file && (dump_flags & TDF_DETAILS))
    dump_rdg (dump_file, rdg);

  FOR_EACH_VEC_ELT (stmts, i, s)
    {
      int v = rdg_vertex_for_stmt (rdg, s);

      if (v >= 0)
	{
	  vertices.safe_push (v);

	  if (dump_file && (dump_flags & TDF_DETAILS))
	    fprintf (dump_file,
		     "ldist asked to generate code for vertex %d\n", v);
	}
    }

  res = ldist_gen (loop, rdg, vertices);
  vertices.release ();
  free_rdg (rdg);
  free_dependence_relations (dependence_relations);
  free_data_refs (datarefs);
  loop_nest.release ();
  return res;
}

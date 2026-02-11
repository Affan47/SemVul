analyze_all_data_dependences (struct loop *loop)
{
  unsigned int i;
  int nb_data_refs = 10;
  VEC (data_reference_p, heap) *datarefs =
    VEC_alloc (data_reference_p, heap, nb_data_refs);
  VEC (ddr_p, heap) *dependence_relations =
    VEC_alloc (ddr_p, heap, nb_data_refs * nb_data_refs);
  VEC (loop_p, heap) *loop_nest = VEC_alloc (loop_p, heap, 3);


  compute_data_dependences_for_loop (loop, false, &loop_nest, &datarefs,
				     &dependence_relations);

  if (dump_file)
    {
      dump_data_dependence_relations (dump_file, dependence_relations);
      fprintf (dump_file, "\n\n");

      if (dump_flags & TDF_DETAILS)
	dump_dist_dir_vectors (dump_file, dependence_relations);

      if (dump_flags & TDF_STATS)
	{
	  unsigned nb_top_relations = 0;
	  unsigned nb_bot_relations = 0;
	  unsigned nb_chrec_relations = 0;
	  struct data_dependence_relation *ddr;

	  FOR_EACH_VEC_ELT (ddr_p, dependence_relations, i, ddr)
	    {
	      if (chrec_contains_undetermined (DDR_ARE_DEPENDENT (ddr)))
		nb_top_relations++;

	      else if (DDR_ARE_DEPENDENT (ddr) == chrec_known)
		nb_bot_relations++;

	      else
		nb_chrec_relations++;
	    }

	  gather_stats_on_scev_database ();
	}
    }

  VEC_free (loop_p, heap, loop_nest);
  free_dependence_relations (dependence_relations);
  free_data_refs (datarefs);
}

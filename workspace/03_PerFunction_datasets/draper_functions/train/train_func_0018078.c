vect_slp_analyze_bb_1 (basic_block bb)
{
  bb_vec_info bb_vinfo;
  VEC (ddr_p, heap) *ddrs;
  VEC (slp_instance, heap) *slp_instances;
  slp_instance instance;
  int i;
  int min_vf = 2;
  int max_vf = MAX_VECTORIZATION_FACTOR;

  bb_vinfo = new_bb_vec_info (bb);
  if (!bb_vinfo)
    return NULL;

  if (!vect_analyze_data_refs (NULL, bb_vinfo, &min_vf))
    {
      if (vect_print_dump_info (REPORT_UNVECTORIZED_LOCATIONS))
        fprintf (vect_dump, "not vectorized: unhandled data-ref in basic "
                            "block.\n");

      destroy_bb_vec_info (bb_vinfo);
      return NULL;
    }

  ddrs = BB_VINFO_DDRS (bb_vinfo);
  if (!VEC_length (ddr_p, ddrs))
    {
      if (vect_print_dump_info (REPORT_UNVECTORIZED_LOCATIONS))
        fprintf (vect_dump, "not vectorized: not enough data-refs in basic "
                            "block.\n");

      destroy_bb_vec_info (bb_vinfo);
      return NULL;
    }

  vect_pattern_recog (NULL, bb_vinfo);

  if (!vect_analyze_data_ref_dependences (NULL, bb_vinfo, &max_vf)
       || min_vf > max_vf)
     {
       if (vect_print_dump_info (REPORT_UNVECTORIZED_LOCATIONS))
	 fprintf (vect_dump, "not vectorized: unhandled data dependence "
		  "in basic block.\n");

       destroy_bb_vec_info (bb_vinfo);
       return NULL;
     }

  if (!vect_analyze_data_refs_alignment (NULL, bb_vinfo))
    {
      if (vect_print_dump_info (REPORT_UNVECTORIZED_LOCATIONS))
        fprintf (vect_dump, "not vectorized: bad data alignment in basic "
                            "block.\n");

      destroy_bb_vec_info (bb_vinfo);
      return NULL;
    }

  if (!vect_analyze_data_ref_accesses (NULL, bb_vinfo))
    {
     if (vect_print_dump_info (REPORT_UNVECTORIZED_LOCATIONS))
       fprintf (vect_dump, "not vectorized: unhandled data access in basic "
                           "block.\n");

      destroy_bb_vec_info (bb_vinfo);
      return NULL;
    }


  if (!vect_analyze_slp (NULL, bb_vinfo))
    {
      if (vect_print_dump_info (REPORT_UNVECTORIZED_LOCATIONS))
        fprintf (vect_dump, "not vectorized: failed to find SLP opportunities "
                            "in basic block.\n");

      destroy_bb_vec_info (bb_vinfo);
      return NULL;
    }

  slp_instances = BB_VINFO_SLP_INSTANCES (bb_vinfo);


  FOR_EACH_VEC_ELT (slp_instance, slp_instances, i, instance)
    {
      vect_mark_slp_stmts (SLP_INSTANCE_TREE (instance), pure_slp, -1);
      vect_mark_slp_stmts_relevant (SLP_INSTANCE_TREE (instance));
    }

   if (!vect_verify_datarefs_alignment (NULL, bb_vinfo))
    {
      if (vect_print_dump_info (REPORT_UNVECTORIZED_LOCATIONS))
        fprintf (vect_dump, "not vectorized: unsupported alignment in basic "
                            "block.\n");

      destroy_bb_vec_info (bb_vinfo);
      return NULL;
    }

  if (!vect_slp_analyze_operations (bb_vinfo))
    {
      if (vect_print_dump_info (REPORT_UNVECTORIZED_LOCATIONS))
        fprintf (vect_dump, "not vectorized: bad operation in basic block.\n");

      destroy_bb_vec_info (bb_vinfo);
      return NULL;
    }


  if (flag_vect_cost_model
      && !vect_bb_vectorization_profitable_p (bb_vinfo))
    {
      if (vect_print_dump_info (REPORT_UNVECTORIZED_LOCATIONS))
        fprintf (vect_dump, "not vectorized: vectorization is not "
                            "profitable.\n");

      destroy_bb_vec_info (bb_vinfo);
      return NULL;
    }

  if (vect_print_dump_info (REPORT_DETAILS))
    fprintf (vect_dump, "Basic block will be vectorized using SLP\n");

  return bb_vinfo;
}

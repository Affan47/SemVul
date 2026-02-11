compute_all_dependences (VEC (data_reference_p, heap) *datarefs,
			 VEC (ddr_p, heap) **dependence_relations,
			 VEC (loop_p, heap) *loop_nest,
			 bool compute_self_and_rr)
{
  struct data_dependence_relation *ddr;
  struct data_reference *a, *b;
  unsigned int i, j;

  if ((int) VEC_length (data_reference_p, datarefs)
      > PARAM_VALUE (PARAM_LOOP_MAX_DATAREFS_FOR_DATADEPS))
    {
      struct data_dependence_relation *ddr;


      ddr = initialize_data_dependence_relation (NULL, NULL, loop_nest);
      VEC_safe_push (ddr_p, heap, *dependence_relations, ddr);
      return false;
    }

  FOR_EACH_VEC_ELT (data_reference_p, datarefs, i, a)
    for (j = i + 1; VEC_iterate (data_reference_p, datarefs, j, b); j++)
      if (DR_IS_WRITE (a) || DR_IS_WRITE (b) || compute_self_and_rr)
	{
	  ddr = initialize_data_dependence_relation (a, b, loop_nest);
	  VEC_safe_push (ddr_p, heap, *dependence_relations, ddr);
          if (loop_nest)
   	    compute_affine_dependence (ddr, VEC_index (loop_p, loop_nest, 0));
	}

  if (compute_self_and_rr)
    FOR_EACH_VEC_ELT (data_reference_p, datarefs, i, a)
      {
	ddr = initialize_data_dependence_relation (a, a, loop_nest);
	VEC_safe_push (ddr_p, heap, *dependence_relations, ddr);
        if (loop_nest)
   	  compute_affine_dependence (ddr, VEC_index (loop_p, loop_nest, 0));
      }

  return true;
}

loop_parallel_p (struct loop *loop, struct obstack * parloop_obstack)
{
  VEC (loop_p, heap) *loop_nest;
  VEC (ddr_p, heap) *dependence_relations;
  VEC (data_reference_p, heap) *datarefs;
  lambda_trans_matrix trans;
  bool ret = false;

  if (dump_file && (dump_flags & TDF_DETAILS))
  {
    fprintf (dump_file, "Considering loop %d\n", loop->num);
    if (!loop->inner)
      fprintf (dump_file, "loop is innermost\n");
    else
      fprintf (dump_file, "loop NOT innermost\n");
   }


  datarefs = VEC_alloc (data_reference_p, heap, 10);
  dependence_relations = VEC_alloc (ddr_p, heap, 10 * 10);
  loop_nest = VEC_alloc (loop_p, heap, 3);
  if (! compute_data_dependences_for_loop (loop, true, &loop_nest, &datarefs,
					   &dependence_relations))
    {
      if (dump_file && (dump_flags & TDF_DETAILS))
	fprintf (dump_file, "  FAILED: cannot analyze data dependencies\n");
      ret = false;
      goto end;
    }
  if (dump_file && (dump_flags & TDF_DETAILS))
    dump_data_dependence_relations (dump_file, dependence_relations);

  trans = lambda_trans_matrix_new (1, 1, parloop_obstack);
  LTM_MATRIX (trans)[0][0] = -1;

  if (lambda_transform_legal_p (trans, 1, dependence_relations))
    {
      ret = true;
      if (dump_file && (dump_flags & TDF_DETAILS))
	fprintf (dump_file, "  SUCCESS: may be parallelized\n");
    }
  else if (dump_file && (dump_flags & TDF_DETAILS))
    fprintf (dump_file,
	     "  FAILED: data dependencies exist across iterations\n");

 end:
  VEC_free (loop_p, heap, loop_nest);
  free_dependence_relations (dependence_relations);
  free_data_refs (datarefs);

  return ret;
}

ddr_consistent_p (FILE *file,
		  struct data_dependence_relation *ddr,
		  vec<lambda_vector> dist_vects,
		  vec<lambda_vector> dir_vects)
{
  unsigned int i, j;


  if (dump_file && (dump_flags & TDF_DETAILS))
    file = dump_file;

  if (dist_vects.length () != DDR_NUM_DIST_VECTS (ddr))
    {
      lambda_vector b_dist_v;
      fprintf (file, "\n(Number of distance vectors differ: Banerjee has %d, Omega has %d.\n",
	       dist_vects.length (),
	       DDR_NUM_DIST_VECTS (ddr));

      fprintf (file, "Banerjee dist vectors:\n");
      FOR_EACH_VEC_ELT (dist_vects, i, b_dist_v)
	print_lambda_vector (file, b_dist_v, DDR_NB_LOOPS (ddr));

      fprintf (file, "Omega dist vectors:\n");
      for (i = 0; i < DDR_NUM_DIST_VECTS (ddr); i++)
	print_lambda_vector (file, DDR_DIST_VECT (ddr, i), DDR_NB_LOOPS (ddr));

      fprintf (file, "data dependence relation:\n");
      dump_data_dependence_relation (file, ddr);

      fprintf (file, ")\n");
      return false;
    }

  if (dir_vects.length () != DDR_NUM_DIR_VECTS (ddr))
    {
      fprintf (file, "\n(Number of direction vectors differ: Banerjee has %d, Omega has %d.)\n",
	       dir_vects.length (),
	       DDR_NUM_DIR_VECTS (ddr));
      return false;
    }

  for (i = 0; i < DDR_NUM_DIST_VECTS (ddr); i++)
    {
      lambda_vector a_dist_v;
      lambda_vector b_dist_v = DDR_DIST_VECT (ddr, i);


      FOR_EACH_VEC_ELT (dist_vects, j, a_dist_v)
	if (lambda_vector_equal (a_dist_v, b_dist_v, DDR_NB_LOOPS (ddr)))
	  break;

      if (j == dist_vects.length ())
	{
	  fprintf (file, "\n(Dist vectors from the first dependence analyzer:\n");
	  print_dist_vectors (file, dist_vects, DDR_NB_LOOPS (ddr));
	  fprintf (file, "not found in Omega dist vectors:\n");
	  print_dist_vectors (file, DDR_DIST_VECTS (ddr), DDR_NB_LOOPS (ddr));
	  fprintf (file, "data dependence relation:\n");
	  dump_data_dependence_relation (file, ddr);
	  fprintf (file, ")\n");
	}
    }

  for (i = 0; i < DDR_NUM_DIR_VECTS (ddr); i++)
    {
      lambda_vector a_dir_v;
      lambda_vector b_dir_v = DDR_DIR_VECT (ddr, i);


      FOR_EACH_VEC_ELT (dir_vects, j, a_dir_v)
	if (lambda_vector_equal (a_dir_v, b_dir_v, DDR_NB_LOOPS (ddr)))
	  break;

      if (j == dist_vects.length ())
	{
	  fprintf (file, "\n(Dir vectors from the first dependence analyzer:\n");
	  print_dir_vectors (file, dir_vects, DDR_NB_LOOPS (ddr));
	  fprintf (file, "not found in Omega dir vectors:\n");
	  print_dir_vectors (file, DDR_DIR_VECTS (ddr), DDR_NB_LOOPS (ddr));
	  fprintf (file, "data dependence relation:\n");
	  dump_data_dependence_relation (file, ddr);
	  fprintf (file, ")\n");
	}
    }

  return true;
}

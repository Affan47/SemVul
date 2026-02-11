build_classic_dir_vector (struct data_dependence_relation *ddr)
{
  unsigned i, j;
  lambda_vector dist_v;

  FOR_EACH_VEC_ELT (DDR_DIST_VECTS (ddr), i, dist_v)
    {
      lambda_vector dir_v = lambda_vector_new (DDR_NB_LOOPS (ddr));

      for (j = 0; j < DDR_NB_LOOPS (ddr); j++)
	dir_v[j] = dir_from_dist (dist_v[j]);

      save_dir_v (ddr, dir_v);
    }
}

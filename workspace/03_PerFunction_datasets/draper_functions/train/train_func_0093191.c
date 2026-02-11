insert_innermost_unit_dist_vector (struct data_dependence_relation *ddr)
{
  lambda_vector dist_v = lambda_vector_new (DDR_NB_LOOPS (ddr));

  dist_v[DDR_INNER_LOOP (ddr)] = 1;
  save_dist_v (ddr, dist_v);
}

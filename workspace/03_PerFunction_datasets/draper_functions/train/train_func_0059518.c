gimple_build_omp_critical (gimple_seq body, tree name)
{
  gimple p = gimple_alloc (GIMPLE_OMP_CRITICAL, 0);
  gimple_omp_critical_set_name (p, name);
  if (body)
    gimple_omp_set_body (p, body);

  return p;
}

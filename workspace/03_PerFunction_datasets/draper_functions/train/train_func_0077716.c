init_multipole_code() {
  if(global_initialized_flag)
    return 0;
  for(int l = 0; l <= MAX_MULTIPOLE_DEGREE; l++)
    for(int m = 0; m <= l; m++)
      global_lm_factor_list[l][m] = get_lm_factor_slow(l, m);
  global_initialized_flag = 1;

  for(int A = 0; A < MAX_NO_OF_MOMENTS_PER_MULTIPOLE; A++)
    get_l_m_from_index(A, &global_l_m_list[A].l, &global_l_m_list[A].m);
  return 0;
}

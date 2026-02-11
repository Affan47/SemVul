operator=(const vnl_random& r)
{
  linear_congruential_previous=r.linear_congruential_previous;
  mz_array_position=r.mz_array_position;
  mz_borrow=r.mz_borrow;
  mz_previous_normal_flag=r.mz_previous_normal_flag;
  for (unsigned int i=0;i<vnl_random_array_size;++i)
  {
    mz_seed_array[i] = r.mz_seed_array[i];
    mz_array[i] = r.mz_array[i];
  }
  return *this;
}

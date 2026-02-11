random_shuffle_array_uint8_2_test (void)
{
  const int sample_size = 1000;
  const double epsilon = 0.000001;

  const unsigned int seed = 775533;
  random_init_seed_with_value(seed);

  const double expected_chi_square = 1.444000;

  const int s_size = 2;
  const int s_sum = 1;
  uint8_t s[] = {0, 1};

  unsigned long s_observations[2][2] = {{0, 0}, {0, 0}};
  double s_probabilities[2][2] = {{0.5, 0.5}, {0.5, 0.5}};

  for (int i = 0; i < sample_size; i++) {
    int sum = 0;
    for (int j = 0; j < s_size; j++) {
      s[j] = j;
    }
    random_shuffle_array_uint8(s, s_size);
    for (int j = 0; j < s_size; j++) {
      g_assert(s[j] >= 0 && s[j] <= s_size - 1);
      sum += s[j];
      s_observations[j][s[j]]++;
    }
    g_assert(sum == s_sum);
  }

  for (int i = 0; i < s_size; i++) {
    double chi_square = hlp_chi_square(&s_observations[i][0], &s_probabilities[i][0], s_size, sample_size);
    g_assert_cmpfloat(fabs(chi_square - expected_chi_square), <=, epsilon);
  }

}

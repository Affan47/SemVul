sort_utils_smoothsort_test (void)
{
  double a[]        = { 7., 3., 9., 0., 1., 5., 2., 8., 4., 6. };
  double expected[] = { 0., 1., 2., 3., 4., 5., 6., 7., 8., 9. };

  const int a_length = sizeof(a) / sizeof(a[0]);

  sort_utils_smoothsort(a, a_length, sizeof(double), sort_utils_double_le);

  for (int i = 0; i < a_length; i++) {
    g_assert_cmpfloat(expected[i], ==, a[i]);
  }
}

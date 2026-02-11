main (int   argc,
      char *argv[])
{
  g_test_init (&argc, &argv, NULL);

  g_test_add_func("/sort_utils/dummy", dummy_test);

  g_test_add_func("/sort_utils/sort_utils_double_compare_test", sort_utils_double_compare_test);

  g_test_add("/sort_utils/sort_utils_insertionsort_tc_double_base_test",
             Fixture,
             (gconstpointer) tc_double_base,
             base_fixture_setup,
             sort_utils_insertionsort_tc_double_base_test,
             base_fixture_teardown);

  g_test_add_func("/sort_utils/sort_utils_insertionsort_asc_d_1_test", sort_utils_insertionsort_asc_d_1_test);

  g_test_add("/sort_utils/sort_utils_heapsort_tc_double_base_test",
             Fixture,
             (gconstpointer) tc_double_base,
             base_fixture_setup,
             sort_utils_heapsort_tc_double_base_test,
             base_fixture_teardown);
  g_test_add_func("/sort_utils/sort_utils_heapsort_asc_d_1_test", sort_utils_heapsort_asc_d_1_test);

  g_test_add("/sort_utils/sort_utils_smoothsort_tc_double_base_test",
             Fixture,
             (gconstpointer) tc_double_base,
             base_fixture_setup,
             sort_utils_smoothsort_tc_double_base_test,
             base_fixture_teardown);

  g_test_add_func("/sort_utils/sort_utils_smoothsort_d_0_test", sort_utils_smoothsort_d_0_test);
  g_test_add_func("/sort_utils/sort_utils_smoothsort_d_1_test", sort_utils_smoothsort_d_1_test);

  g_test_add_func("/sort_utils/sort_utils_smoothsort_test", sort_utils_smoothsort_test);

  if (g_test_perf()) {
    g_test_add_func("/sort_utils/sort_utils_insertionsort_asc_d_perf_test", sort_utils_insertionsort_asc_d_perf_test);
    g_test_add_func("/sort_utils/sort_utils_heapsort_asc_d_perf_test", sort_utils_heapsort_asc_d_perf_test);
    g_test_add_func("/sort_utils/sort_utils_smoothsort_d_perf_test", sort_utils_smoothsort_d_perf_test);
    g_test_add_func("/sort_utils/sort_utils_smoothsort_perf_test", sort_utils_smoothsort_perf_test);
  }

  return g_test_run();
}

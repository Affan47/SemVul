run (int num_iters)
{
  int i;
  s = suite_create ("Stress");
  tc = tcase_create ("Stress");
  sr = srunner_create (s);
  suite_add_tcase(s, tc);

  for (i = 0; i < num_iters; i++) {
    tcase_add_test (tc, test_pass);
    tcase_add_test (tc, test_fail);
  }

  srunner_run_all(sr, CK_SILENT);
  if (srunner_ntests_failed (sr) != num_iters) {
    printf ("Error: expected %d failures, got %d\n",
	    num_iters, srunner_ntests_failed(sr));
    return;
  }

  srunner_free(sr);
}

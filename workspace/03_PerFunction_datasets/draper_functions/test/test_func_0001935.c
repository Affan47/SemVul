test_unicode_properties (gconstpointer user_data)
{
  hb_unicode_funcs_t *uf = (hb_unicode_funcs_t *) user_data;
  unsigned int i, j;
  gboolean failed = TRUE;

  g_assert (hb_unicode_funcs_is_immutable (uf));
  g_assert (hb_unicode_funcs_get_parent (uf));

  for (i = 0; i < G_N_ELEMENTS (properties); i++) {
    const property_t *p = &properties[i];
    const test_pair_t *tests;

    g_test_message ("Testing property %s", p->name);
    tests = p->tests;
    for (j = 0; j < p->num_tests; j++) {
      g_test_message ("Test %s #%d: U+%04X", p->name, j, tests[j].unicode);
      g_assert_cmphex (p->getter (uf, tests[j].unicode), ==, tests[j].value);
    }


    tests = p->tests_more;
    for (j = 0; j < p->num_tests_more; j++) {
      g_test_message ("Test %s more #%d: U+%04X", p->name, j, tests[j].unicode);
      if (p->getter (uf, tests[j].unicode) != tests[j].value) {
	g_test_message ("Soft fail: Received %x, expected %x", p->getter (uf, tests[j].unicode), tests[j].value);
        failed = TRUE;
      }
    }
  }

  if (failed)
    g_test_message ("Some property tests failed.  You probably have an old version of one of the libraries used.");
}

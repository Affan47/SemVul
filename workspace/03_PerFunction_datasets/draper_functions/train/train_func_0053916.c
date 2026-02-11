cut_test_suite_run_test (CutTestSuite *suite, CutRunContext *run_context,
                         gchar *test_name)
{
    GList *test_cases;
    const gchar *test_names[] = {NULL, NULL};

    g_return_val_if_fail(CUT_IS_TEST_SUITE(suite), FALSE);

    test_names[0] = test_name;
    test_cases = cut_test_container_get_children(CUT_TEST_CONTAINER(suite));
    return cut_test_suite_run_test_cases(suite, run_context,
                                         test_cases, test_names);
}

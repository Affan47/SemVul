cut_test_case_run_with_filter (CutTestCase *test_case,
                               CutRunContext *run_context,
                               const gchar **test_names)
{
    GList *filtered_tests;
    gboolean success = TRUE;

    filtered_tests = get_filtered_tests(test_case, test_names);
    if (!filtered_tests)
        return TRUE;

    success = cut_test_case_run_tests(test_case, run_context, filtered_tests);

    g_list_free(filtered_tests);

    return success;
}

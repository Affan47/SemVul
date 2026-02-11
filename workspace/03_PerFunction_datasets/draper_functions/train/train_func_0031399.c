compare_test_cases_by_name (gconstpointer a, gconstpointer b, gpointer user_data)
{
    CutTestCase *test_case1, *test_case2;
    const gchar *test_case_name1, *test_case_name2;
    gboolean ascending;

    test_case1 = CUT_TEST_CASE(a);
    test_case2 = CUT_TEST_CASE(b);
    test_case_name1 = cut_test_get_name(CUT_TEST(test_case1));
    test_case_name2 = cut_test_get_name(CUT_TEST(test_case2));
    ascending = *(gboolean *)user_data;

    if (ascending)
        return strcmp(test_case_name1, test_case_name2);
    else
        return strcmp(test_case_name2, test_case_name1);
}

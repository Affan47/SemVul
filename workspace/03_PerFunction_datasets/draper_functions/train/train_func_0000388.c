start_test_context (CutStreamParserPrivate *priv, GMarkupParseContext *context,
                    const gchar *element_name, GError **error)
{
    if (g_str_equal("test-suite", element_name)) {
        CutTestSuite *test_suite;

        PUSH_STATE(priv, IN_TEST_SUITE);
        test_suite = cut_test_suite_new_empty();
        cut_test_context_set_test_suite(PEEK_TEST_CONTEXT(priv), test_suite);
        PUSH_TEST_SUITE(priv, test_suite);
        g_object_unref(test_suite);
    } else if (g_str_equal("test-case", element_name)) {
        CutTestCase *test_case;

        PUSH_STATE(priv, IN_TEST_CASE);
        test_case = cut_test_case_new_empty();
        cut_test_context_set_test_case(PEEK_TEST_CONTEXT(priv), test_case);
        PUSH_TEST_CASE(priv, test_case);
        g_object_unref(test_case);
    } else if (g_str_equal("test-iterator", element_name)) {
        CutTestIterator *test_iterator;

        PUSH_STATE(priv, IN_TEST_ITERATOR);
        test_iterator = cut_test_iterator_new_empty();
        cut_test_context_set_test_iterator(PEEK_TEST_CONTEXT(priv),
                                           test_iterator);
        PUSH_TEST_ITERATOR(priv, test_iterator);
        g_object_unref(test_iterator);
    } else if (g_str_equal("test", element_name)) {
        CutTest *test;

        PUSH_STATE(priv, IN_TEST);
        test = cut_test_new_empty();
        cut_test_context_set_test(PEEK_TEST_CONTEXT(priv), test);
        PUSH_TEST(priv, test);
        g_object_unref(test);
    } else if (g_str_equal("iterated-test", element_name)) {
        CutIteratedTest *iterated_test;

        PUSH_STATE(priv, IN_ITERATED_TEST);
        iterated_test = cut_iterated_test_new_empty();
        cut_test_context_set_test(PEEK_TEST_CONTEXT(priv),
                                  CUT_TEST(iterated_test));
        PUSH_TEST(priv, CUT_TEST(iterated_test));
        g_object_unref(iterated_test);
    } else if (g_str_equal("test-data", element_name)) {
        CutTestData *test_data;

        PUSH_STATE(priv, IN_TEST_DATA);
        test_data = cut_test_data_new_empty();
        cut_test_context_set_data(PEEK_TEST_CONTEXT(priv), test_data);
        PUSH_TEST_DATA(priv, test_data);
        g_object_unref(test_data);
    } else if (g_str_equal("failed", element_name)) {
        PUSH_STATE(priv, IN_TEST_CONTEXT_FAILED);
    } else {
        invalid_element(priv, context, error);
    }
}

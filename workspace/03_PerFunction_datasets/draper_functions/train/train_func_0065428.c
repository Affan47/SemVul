start_test_object (CutStreamParserPrivate *priv, GMarkupParseContext *context,
                   const gchar *element_name, GError **error)
{
    if (g_str_equal("name", element_name)) {
        PUSH_STATE(priv, IN_TEST_NAME);
    } else if (g_str_equal("description", element_name)) {
        PUSH_STATE(priv, IN_TEST_DESCRIPTION);
    } else if (g_str_equal("option", element_name)) {
        PUSH_STATE(priv, IN_TEST_OPTION);
    } else if (g_str_equal("start-time", element_name)) {
        PUSH_STATE(priv, IN_TEST_START_TIME);
    } else if (g_str_equal("elapsed", element_name)) {
        PUSH_STATE(priv, IN_TEST_ELAPSED);
    } else {
        invalid_element(priv, context, error);
    }
}

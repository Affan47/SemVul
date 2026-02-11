end_test_result (CutStreamParser *parser, CutStreamParserPrivate *priv,
                 GMarkupParseContext *context,
                 const gchar *element_name, GError **error)
{
    if (!priv->test_result)
        return;

    if (priv->run_context) {
        CutTestResult *result;
        CutTestResultStatus status;
        const gchar *signal_name;
        gchar *full_signal_name;

        result = priv->test_result->result;
        status = cut_test_result_get_status(result);
        signal_name = cut_test_result_status_to_signal_name(status);
        full_signal_name = g_strdup_printf("%s-test", signal_name);
        g_signal_emit_by_name(priv->run_context, full_signal_name,
                              priv->test_result->test,
                              priv->test_result->test_context,
                              result);
        g_free(full_signal_name);
    }

    if (priv->test_result->test)
        DROP_TEST(priv);
    if (priv->test_result->test_context)
        DROP_TEST_CONTEXT(priv);
    test_result_free(priv->test_result);
    priv->test_result = NULL;
    priv->result = NULL;
}

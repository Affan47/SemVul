end_test_iterator_result (CutStreamParser *parser, CutStreamParserPrivate *priv,
                          GMarkupParseContext *context,
                          const gchar *element_name, GError **error)
{
    if (!priv->test_iterator_result)
        return;

    if (priv->run_context) {
        CutTestResult *result;
        CutTestResultStatus status;
        const gchar *signal_name;
        gchar *full_signal_name;

        result = priv->test_iterator_result->result;
        status = cut_test_result_get_status(result);
        signal_name = cut_test_result_status_to_signal_name(status);
        full_signal_name = g_strdup_printf("%s-test-iterator", signal_name);
        g_signal_emit_by_name(priv->run_context, full_signal_name,
                              priv->test_iterator_result->test_iterator,
                              priv->test_iterator_result->result);
        g_free(full_signal_name);
    }

    if (priv->test_iterator_result->test_iterator)
        DROP_TEST_ITERATOR(priv);
    test_iterator_result_free(priv->test_iterator_result);
    priv->test_iterator_result = NULL;
    g_object_unref(priv->result);
    priv->result = NULL;
}

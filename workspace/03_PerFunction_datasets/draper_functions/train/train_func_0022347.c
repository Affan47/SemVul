end_complete_test (CutStreamParser *parser, CutStreamParserPrivate *priv,
                   GMarkupParseContext *context,
                   const gchar *element_name, GError **error)
{
    if (!priv->complete_test)
        return;

    if (priv->run_context)
        g_signal_emit_by_name(priv->run_context, "complete-test",
                              priv->complete_test->test,
                              priv->complete_test->test_context,
                              priv->complete_success);

    if (priv->complete_test->test)
        DROP_TEST(priv);
    if (priv->complete_test->test_context)
        DROP_TEST_CONTEXT(priv);
    complete_test_free(priv->complete_test);
    priv->complete_test = NULL;
    priv->complete_success = TRUE;
}

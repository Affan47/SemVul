cut_test_context_set_actual (CutTestContext *context, const gchar *actual)
{
    CutTestContextPrivate *priv;

    priv = CUT_TEST_CONTEXT_GET_PRIVATE(context);
    if (priv->actual)
        g_free(priv->actual);
    priv->actual = g_strdup(actual);
}

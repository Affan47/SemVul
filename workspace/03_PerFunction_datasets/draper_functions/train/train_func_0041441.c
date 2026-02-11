cut_test_context_shift_data (CutTestContext *context)
{
    CutTestContextPrivate *priv;

    priv = CUT_TEST_CONTEXT_GET_PRIVATE(context);

    if (priv->current_data)
        priv->current_data = g_list_previous(priv->current_data);
}

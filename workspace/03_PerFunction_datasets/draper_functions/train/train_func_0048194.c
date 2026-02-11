cut_test_context_pass_assertion (CutTestContext *context)
{
    CutTestContextPrivate *priv;

    g_return_if_fail(CUT_IS_TEST_CONTEXT(context));

    priv = CUT_TEST_CONTEXT_GET_PRIVATE(context);
    g_return_if_fail(priv->test);

    clear_user_message(priv);
    g_signal_emit_by_name(priv->test, "pass-assertion", context);
}

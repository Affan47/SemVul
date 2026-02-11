cut_test_context_emit_signal (CutTestContext *context,
                              CutTestResult *result)
{
    CutTestContextPrivate *priv;
    CutTest *target = NULL;

    priv = CUT_TEST_CONTEXT_GET_PRIVATE(context);
    if (priv->test) {
        target = priv->test;
    } else if (priv->test_iterator) {
        target = CUT_TEST(priv->test_iterator);
    } else if (priv->test_case) {
        target = CUT_TEST(priv->test_case);
    }

    if (target)
        cut_test_emit_result_signal(target, context, result);
}

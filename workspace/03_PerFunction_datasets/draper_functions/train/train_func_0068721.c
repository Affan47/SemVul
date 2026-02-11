cut_test_get_full_name (CutTest *test)
{
    CutTestPrivate *priv;
    CutTestData *data = NULL;

    priv = CUT_TEST_GET_PRIVATE(test);
    if (priv->full_name)
        return priv->full_name;

    if (CUT_IS_ITERATED_TEST(test))
        data = cut_iterated_test_get_data(CUT_ITERATED_TEST(test));

    if (priv->name && data) {
        priv->full_name = g_strconcat(priv->name,
                                      " (",
                                      cut_test_data_get_name(data),
                                      ")",
                                      NULL);
    } else if (priv->name) {
        priv->full_name = g_strdup(priv->name);
    } else if (data) {
        priv->full_name = g_strconcat(" (",
                                      cut_test_data_get_name(data),
                                      ")",
                                      NULL);
    }

    return priv->full_name;
}

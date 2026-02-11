cut_test_container_add_test (CutTestContainer *container, CutTest *test)
{
    CutTestContainerPrivate *priv = CUT_TEST_CONTAINER_GET_PRIVATE(container);

    if (CUT_IS_TEST(test)) {
        g_object_ref(test);
        priv->tests = g_list_append(priv->tests, test);
    }
}

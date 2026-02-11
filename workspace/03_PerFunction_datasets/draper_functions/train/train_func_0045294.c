gth_test_chain_clear_tests (GthTestChain *chain)
{
	if (chain->priv->tests == NULL)
		return;
	_g_object_list_unref (chain->priv->tests);
	chain->priv->tests = NULL;
	g_object_set (chain, "attributes", "", NULL);
}

pk_results_set_error_code (PkResults *results, PkError *item)
{
	g_return_val_if_fail (PK_IS_RESULTS (results), FALSE);
	g_return_val_if_fail (item != NULL, FALSE);


	if (results->priv->error_code != NULL)
		g_object_unref (results->priv->error_code);
	results->priv->error_code = g_object_ref (item);

	return TRUE;
}

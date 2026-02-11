isymbol_iter_last (IAnjutaIterable *iterable, GError **err)
{
	GdaDataModel *data_model;
	gint len;
	SymbolDBQueryResult *result;

	g_return_val_if_fail (SYMBOL_DB_IS_QUERY_RESULT (iterable), FALSE);
	result = SYMBOL_DB_QUERY_RESULT (iterable);
	g_object_get (G_OBJECT (result->priv->iter), "data-model", &data_model, NULL);
	len = gda_data_model_get_n_rows (data_model);
	g_object_unref (data_model);
	if (len <= 0)
		return FALSE;
	return gda_data_model_iter_move_to_row (result->priv->iter, len - 1);
}

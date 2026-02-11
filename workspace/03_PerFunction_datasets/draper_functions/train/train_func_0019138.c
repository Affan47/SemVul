isymbol_iter_previous (IAnjutaIterable *iterable, GError **err)
{
	SymbolDBQueryResult *result;

	g_return_val_if_fail (SYMBOL_DB_IS_QUERY_RESULT (iterable), FALSE);
	result = SYMBOL_DB_QUERY_RESULT (iterable);
	return gda_data_model_iter_move_prev (result->priv->iter);
}

gda_data_proxy_get_values (GdaDataProxy *proxy, gint proxy_row, gint *cols_index, gint n_cols)
{
	GSList *retval = NULL;
	gint i;
	const GValue *value;

	g_return_val_if_fail (GDA_IS_DATA_PROXY (proxy), NULL);
	g_return_val_if_fail (proxy->priv, NULL);
	g_return_val_if_fail (proxy_row >= 0, NULL);

	gda_mutex_lock (proxy->priv->mutex);
	for (i = 0; i < n_cols; i++) {
		value = gda_data_proxy_get_value_at ((GdaDataModel *) proxy, cols_index[i], proxy_row, NULL);
		if (value)
			retval = g_slist_prepend (retval, (GValue *) value);
		else {
			g_slist_free (retval);
			gda_mutex_unlock (proxy->priv->mutex);
			return NULL;
		}
	}
	gda_mutex_unlock (proxy->priv->mutex);

	return g_slist_reverse (retval);
}

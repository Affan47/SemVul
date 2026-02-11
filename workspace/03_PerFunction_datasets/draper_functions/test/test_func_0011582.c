gda_meta_store_modify (GdaMetaStore *store, const gchar *table_name,
	               GdaDataModel *new_data, const gchar *condition, GError **error, ...)
{
	va_list ap;
	gboolean retval;
	gint size = 5, n_values = 0;
	const gchar **value_names;
	const GValue **values;
	gchar *name;

	g_return_val_if_fail (GDA_IS_META_STORE (store), FALSE);
	g_return_val_if_fail (table_name, FALSE);
	g_return_val_if_fail (!new_data || GDA_IS_DATA_MODEL (new_data), FALSE);

	if (store->priv->init_error) {
		g_propagate_error (error, g_error_copy (store->priv->init_error));
		return FALSE;
	}

	value_names = g_new (const gchar *, size);
	values = g_new (const GValue *, size);

	va_start (ap, error);
	for (n_values = 0, name = va_arg (ap, gchar*); name; n_values++, name = va_arg (ap, gchar*)) {
		GValue *v;
		v = va_arg (ap, GValue *);
		if (n_values >= size) {
			size += 5;
			value_names = g_renew (const gchar *, value_names, size);
			values = g_renew (const GValue *, values, size);
		}
		value_names [n_values] = name;
		values [n_values] = v;
	}
	va_end (ap);
	retval = gda_meta_store_modify_v (store, table_name, new_data, condition,
					  n_values, value_names, values, error);
	g_free (value_names);
	g_free (values);
	return retval;
}

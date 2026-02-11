gda_meta_store_get_attribute_value (GdaMetaStore *store, const gchar *att_name, gchar **att_value, GError **error)
{
	GdaDataModel *model;
	GValue *value;
	gint nrows;
	g_return_val_if_fail (GDA_IS_META_STORE (store), FALSE);
	g_return_val_if_fail (att_name && *att_name, FALSE);
	g_return_val_if_fail (att_value, FALSE);

	if (store->priv->init_error) {
		g_propagate_error (error, g_error_copy (store->priv->init_error));
		return FALSE;
	}

	gda_mutex_lock (store->priv->mutex);

	*att_value = NULL;
	g_value_set_string ((value = gda_value_new (G_TYPE_STRING)), att_name);
	model = gda_meta_store_extract (store, "SELECT att_value FROM _attributes WHERE att_name = ##n::string", error,
					"n", value, NULL);
	gda_value_free (value);
	if (!model) {
		gda_mutex_unlock (store->priv->mutex);
		return FALSE;
	}
	nrows = gda_data_model_get_n_rows (model);
	if (nrows < 1)
		g_set_error (error, GDA_META_STORE_ERROR, GDA_META_STORE_ATTRIBUTE_NOT_FOUND_ERROR,
			     _("Attribute '%s' not found"), att_name);
	else if (nrows > 1)
		g_set_error (error, GDA_META_STORE_ERROR, GDA_META_STORE_ATTRIBUTE_ERROR,
			     ngettext ("Attribute '%s' has %d value", "Attribute '%s' has %d values", nrows),
			     att_name, nrows);
	else {
		value = (GValue*) gda_data_model_get_value_at (model, 0, 0, error);
		if (!value) {
			gda_mutex_unlock (store->priv->mutex);
			return FALSE;
		}
		if (G_VALUE_TYPE (value) == G_TYPE_STRING) {
			const gchar *val;
			val = g_value_get_string (value);
			if (val)
				*att_value = g_strdup (val);
		}
		gda_mutex_unlock (store->priv->mutex);
		return TRUE;
	}
	gda_mutex_unlock (store->priv->mutex);
	return FALSE;
}

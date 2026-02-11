midgard_collector_set (MidgardCollector *self, const gchar *key, const gchar *subkey, GValue *value)
{
	g_assert(self != NULL);
	GQuark keyquark = g_quark_from_string(key);
	GData *valueslist;
	GQuark subkeyquark;

	if(subkey == NULL){


		subkeyquark = g_quark_from_string("0");
		valueslist = (GData *) g_datalist_id_get_data(
				&self->priv->datalist,
				subkeyquark);

		if(valueslist == NULL)
			g_datalist_init(&valueslist);

		GValue *val = g_new0(GValue, 1);
		g_value_init(val, G_TYPE_UINT);
		g_value_set_uint(val, 0);
		g_datalist_id_set_data_full (
				&valueslist,
				subkeyquark,
				val,
				_unset_subkey_value);

		g_datalist_id_set_data_full (
				&self->priv->datalist,
				keyquark,
				(gpointer) valueslist,
				__unset_subkey_valuelist);

		return TRUE;
	}

	const gchar *nick =
		_collector_find_class_property(self, subkey);

	if(!nick)
		return FALSE;

	subkeyquark = g_quark_from_string(subkey);
	valueslist = (GData *) g_datalist_id_get_data(
			&self->priv->datalist,
			keyquark);

	if(valueslist == NULL)
		g_datalist_init(&valueslist);

	g_datalist_id_set_data_full (
			&valueslist,
			subkeyquark,
			(gpointer) value,
			_unset_subkey_value);

	g_datalist_id_set_data_full (
			&self->priv->datalist,
			keyquark,
			(gpointer) valueslist,
			__unset_subkey_valuelist);

	return TRUE;
}

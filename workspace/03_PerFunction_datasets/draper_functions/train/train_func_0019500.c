midgard_collector_get_subkey (MidgardCollector *self, const gchar *key, const gchar *subkey)
{
	g_assert(self);

	const gchar *nick;
	nick = _collector_find_class_property(self, subkey);
	if(!nick)
		return NULL;

	if(&self->priv->datalist == NULL){
		g_warning("Collector's key set with NULL value");
		return NULL;
	}

	GData *valueslist = g_datalist_id_get_data (
			&self->priv->datalist,
			g_quark_from_string(key));

	if(!valueslist) {
		g_log(G_LOG_DOMAIN, G_LOG_LEVEL_DEBUG,
				"midgard_collector: No subkeys associated with the given '%s' key",
				key);
		return NULL;
	}

	GValue *value =  g_datalist_id_get_data (
			&valueslist,
			g_quark_from_string(subkey));

	return value;
}

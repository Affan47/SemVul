find_miner_proxy (TrackerMinerManager *manager,
                  const gchar         *name,
                  gboolean             try_suffix)
{
	TrackerMinerManagerPrivate *priv;
	GHashTableIter iter;
	gpointer key, value;

	priv = TRACKER_MINER_MANAGER_GET_PRIVATE (manager);
	g_hash_table_iter_init (&iter, priv->miner_proxies);

	while (g_hash_table_iter_next (&iter, &key, &value)) {
		if (g_strcmp0 (name, (gchar *) value) == 0) {
			return key;
		}

		if (try_suffix) {
			if (g_str_has_suffix (value, name)) {
				return key;
			}
		}
	}

	return NULL;
}

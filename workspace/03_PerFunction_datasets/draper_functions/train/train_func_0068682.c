gconf_client_set_bool (GConfClient *client, const char *key, gboolean val, GError **error)
{
	Value *v;

	g_return_val_if_fail (client != NULL, FALSE);

	v = g_hash_table_lookup (GCONF_CLIENT_GET_PRIVATE (client)->keys, key);
	if (v) {
		if (v->type != GCONF_VALUE_BOOL) {
			g_set_error (error, GCONF_ERROR, GCONF_ERROR_TYPE_MISMATCH, "expected boolean type");
			return FALSE;
		}
		v->v_bool = val;
	} else {
		v = (Value *) gconf_value_new (GCONF_VALUE_BOOL);
		v->v_bool = val;
		g_hash_table_insert (GCONF_CLIENT_GET_PRIVATE (client)->keys, g_strdup (key), v);
	}
	return TRUE;
}

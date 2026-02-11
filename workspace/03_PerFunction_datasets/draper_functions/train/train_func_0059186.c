gconf_client_set_string (GConfClient *client, const char *key, const char *val, GError **error)
{
	Value *v;

	g_return_val_if_fail (client != NULL, FALSE);
	g_return_val_if_fail (val != NULL, FALSE);

	v = g_hash_table_lookup (GCONF_CLIENT_GET_PRIVATE (client)->keys, key);
	if (v) {
		if (v->type != GCONF_VALUE_STRING) {
			g_set_error (error, GCONF_ERROR, GCONF_ERROR_TYPE_MISMATCH, "expected string type");
			return FALSE;
		}
		g_free (v->v_str);
		v->v_str = g_strdup (val);
	} else {
		v = (Value *) gconf_value_new (GCONF_VALUE_STRING);
		v->v_str = g_strdup (val);
		g_hash_table_insert (GCONF_CLIENT_GET_PRIVATE (client)->keys, g_strdup (key), v);
	}
	return TRUE;
}

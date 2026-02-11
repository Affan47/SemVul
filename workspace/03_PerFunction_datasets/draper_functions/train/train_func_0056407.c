g_value_hash_set_value (GValueHash *self,
			const char *key,
			GValue     *value)
{
	GValue *priv_value;

	priv_value = g_new0 (GValue, 1);
	g_value_copy (value, priv_value);
	g_hash_table_insert (self->table, g_strdup (key), priv_value);
}

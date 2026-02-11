gda_sqlite_handler_boolean_get_value_from_sql (G_GNUC_UNUSED GdaDataHandler *iface, const gchar *sql, G_GNUC_UNUSED GType type)
{
	g_assert (sql);

	GValue *value;
	value = g_value_init (g_new0 (GValue, 1), G_TYPE_BOOLEAN);
	if (*sql == '0')
		g_value_set_boolean (value, FALSE);
	else
		g_value_set_boolean (value, TRUE);
	return value;
}

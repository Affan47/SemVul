gnome_scan_settings_set (GnomeScanSettings *settings,
                         const gchar *name,
                         const GValue *value)
{
	g_return_if_fail (GNOME_IS_SCAN_SETTINGS (settings) && G_IS_VALUE (value));
	g_hash_table_insert (GET_PRIVATE (settings)->values, g_strdup (name),
						 g_boxed_copy (G_TYPE_VALUE, value));
	g_signal_emit (settings, signals[CHANGED], 0, name);
}

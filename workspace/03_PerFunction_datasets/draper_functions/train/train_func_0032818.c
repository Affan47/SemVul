gnome_scan_settings_get_object (GnomeScanSettings *settings,
				const gchar *name)
{
  g_return_val_if_fail (GNOME_IS_SCAN_SETTINGS (settings), NULL);
  GValue *v = gnome_scan_settings_get_transformed (settings,
						   name,
						   G_TYPE_OBJECT);
  GObject* val = g_value_dup_object (v);
  g_value_unset (v);
  g_free (v);
  return val;
}

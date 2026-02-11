gwh_settings_save_to_file (GwhSettings *self,
                           const gchar *filename,
                           GError     **error)
{
  GParamSpec  **pspecs;
  guint         n_props;
  guint         i;
  gboolean      success = TRUE;
  GKeyFile     *key_file;

  g_return_val_if_fail (GWH_IS_SETTINGS (self), FALSE);
  g_return_val_if_fail (filename != NULL, FALSE);

  key_file = g_key_file_new ();
  g_key_file_load_from_file (key_file, filename, G_KEY_FILE_KEEP_COMMENTS |
                             G_KEY_FILE_KEEP_TRANSLATIONS, NULL);
  pspecs = g_object_class_list_properties (G_OBJECT_GET_CLASS (self), &n_props);
  for (i = 0; success && i < n_props; i++) {
    GValue  value = {0};

    g_value_init (&value, pspecs[i]->value_type);
    g_object_get_property (G_OBJECT (self), pspecs[i]->name, &value);
    success = key_file_set_value (key_file, pspecs[i]->name, &value, error);
    g_value_unset (&value);
  }
  g_free (pspecs);
  if (success) {
    gchar  *data;
    gsize   length;

    data = g_key_file_to_data (key_file, &length, error);
    if (! data) {
      success = FALSE;
    } else {
      success = g_file_set_contents (filename, data, length, error);
      g_free (data);
    }
  }
  g_key_file_free (key_file);

  return success;
}

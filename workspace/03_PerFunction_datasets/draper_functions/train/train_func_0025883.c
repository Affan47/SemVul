gst_preset_default_set_meta (GstPreset * preset, const gchar * name,
    const gchar * tag, const gchar * value)
{
  GKeyFile *presets;
  gchar *key;


  if (!(presets = preset_get_keyfile (preset)))
    goto no_presets;

  key = g_strdup_printf ("_meta/%s", tag);
  if (value && *value) {
    g_key_file_set_value (presets, name, key, value);
  } else {
    g_key_file_remove_key (presets, name, key, NULL);
  }
  g_free (key);


  return gst_preset_default_save_presets_file (preset);


no_presets:
  {
    GST_WARNING_OBJECT (preset, "no presets");
    return FALSE;
  }
}

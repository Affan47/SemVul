preset_get_keyfile (GstPreset * preset)
{
  GKeyFile *presets;
  GType type = G_TYPE_FROM_INSTANCE (preset);


  if (!(presets = g_type_get_qdata (type, preset_quark))) {
    const gchar *preset_user_path, *preset_app_path, *preset_system_path;
    guint64 version_system = G_GUINT64_CONSTANT (0);
    guint64 version_app = G_GUINT64_CONSTANT (0);
    guint64 version_user = G_GUINT64_CONSTANT (0);
    guint64 version = G_GUINT64_CONSTANT (0);
    gboolean merged = FALSE;
    GKeyFile *in_user, *in_app = NULL, *in_system;

    preset_get_paths (preset, &preset_user_path, &preset_app_path,
        &preset_system_path);


    in_user = preset_open_and_parse_header (preset, preset_user_path,
        &version_user);
    if (preset_app_path) {
      in_app = preset_open_and_parse_header (preset, preset_app_path,
          &version_app);
    }
    in_system = preset_open_and_parse_header (preset, preset_system_path,
        &version_system);


    if (in_system) {
      presets = in_system;
      version = version_system;
    }
    if (in_app) {

      if (version > version_app) {
        preset_merge (presets, in_app);
        g_key_file_free (in_app);
      } else {
        if (presets)
          g_key_file_free (presets);
        presets = in_app;
        version = version_system;
      }
    }
    if (in_user) {

      if (version > version_user) {
        preset_merge (presets, in_user);
        g_key_file_free (in_user);
        merged = TRUE;
      } else {
        if (presets)
          g_key_file_free (presets);
        presets = in_user;
        version = version_user;
      }
    }

    if (!presets) {

      presets = g_key_file_new ();
      g_key_file_set_string (presets, PRESET_HEADER, PRESET_HEADER_ELEMENT_NAME,
          G_OBJECT_TYPE_NAME (preset));
    }


    g_type_set_qdata (type, preset_quark, (gpointer) presets);

    if (merged) {
      gst_preset_default_save_presets_file (preset);
    }
  }
  return presets;
}

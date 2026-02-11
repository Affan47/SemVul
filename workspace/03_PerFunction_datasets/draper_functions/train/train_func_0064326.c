gnac_profiles_mgr_get_file_name(GFile *file,
                                guint  target_type)
{
  GError *error = NULL;

  GFileInfo *file_info = g_file_query_info(file,
      G_FILE_ATTRIBUTE_STANDARD_NAME ","
      G_FILE_ATTRIBUTE_STANDARD_TYPE,
      G_FILE_QUERY_INFO_NONE, NULL, &error);
  if (error) {
    libgnac_warning("%s", error->message);
    g_clear_error(&error);
    return NULL;
  }

  gchar *name = NULL;

  switch (target_type)
  {
    case DND_TARGET_URI:
      if (g_file_info_get_file_type(file_info) == G_FILE_TYPE_REGULAR) {
        name = g_strdup(g_file_info_get_name(file_info));
      }
      break;

    case DND_TARGET_PLAIN:
      if (g_file_info_get_file_type(file_info) == G_FILE_TYPE_UNKNOWN) {
        name = g_file_get_basename(file);
      }
      break;
  }

  g_object_unref(file_info);

  return name;
}

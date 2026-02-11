sw_cache_save (SwService   *service,
               const gchar *query,
               GHashTable  *params,
               SwSet       *set)
{
  char *filename;

  g_return_if_fail (SW_IS_SERVICE (service));

  if (query == NULL)
    query = "feed";

  filename = get_cache_filename (service, query, params);

  if (set == NULL || sw_set_is_empty (set)) {
    g_remove (filename);
  } else {
    GKeyFile *keys;
    char *data;
    GError *error = NULL;

    keys = g_key_file_new ();
    sw_set_foreach (set, set_keyfile_from_item, keys);

    data = g_key_file_to_data (keys, NULL, NULL);
    if (!g_file_set_contents (filename, data, -1, &error)) {
      g_message ("Cannot write cache: %s", error->message);
      g_error_free (error);
    }
    g_free (data);
    g_key_file_free (keys);
  }

  g_free (filename);
}

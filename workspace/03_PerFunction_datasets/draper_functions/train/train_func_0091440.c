mx_texture_cache_filename_to_uri (const gchar *file)
{
  gchar *uri;
  gchar *new_file;
  GError *error = NULL;

  new_file = mx_texture_cache_resolve_relative_path (file);
  if (new_file)
    {
      uri = g_filename_to_uri (new_file, NULL, &error);
      g_free (new_file);
    }
  else
    uri = g_filename_to_uri (file, NULL, &error);

  if (!uri)
    {
      g_warning ("Unable to transform filename to URI: %s",
                 error->message);
      g_error_free (error);
      return NULL;
    }

  return uri;
}

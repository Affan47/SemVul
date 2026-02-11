unity_webapps_script_loader_get_require_contents (UnityWebappsScriptLoader *self,
												  const gchar *require)
{
  const gchar *require_path;
  gchar *contents;
  GError *error;

  require_path = unity_webapps_script_loader_find_require_path (self, require);

  if (require_path == NULL)
	{
	  return NULL;
	}

  error = NULL;
  g_file_get_contents (require_path, &contents, NULL, &error);

  if (error != NULL)
	{
	  g_warning ("Failed to load required script file: %s \n", error->message);
	  g_error_free (error);

	  return NULL;
	}
  return contents;
}

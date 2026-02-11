unity_webapps_script_loader_find_require_path_in_data_dir (UnityWebappsScriptLoader *loader, const gchar *data_dir, const gchar *require)
{
  gchar *require_file;
  gboolean exists;

  require_file = g_build_filename (data_dir, "unity-webapps/userscripts/common", require, NULL);
  exists = g_file_test (require_file, G_FILE_TEST_EXISTS);

  if (exists)
	{
	  return require_file;
	}
  else
	{
	  g_free (require_file);
	}

  return NULL;
}

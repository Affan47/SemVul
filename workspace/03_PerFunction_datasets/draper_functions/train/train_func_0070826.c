unity_webapps_script_loader_get_combined_requirements (UnityWebappsScriptLoader *self,
													   UnityWebappsApplicationManifest *manifest)
{
  GString *combined_requirements;
  const gchar **require_files;
  gchar *ret;
  gint i, len;

  require_files = unity_webapps_application_manifest_get_requires (manifest);
  if (require_files == NULL)
	{
	  return NULL;
	}
  combined_requirements = g_string_new ("");


  len = g_strv_length ((gchar **)require_files);
  for (i = 0; i < len; i++)
	{
	  const gchar *require_file;
	  gchar *contents;

	  require_file = require_files[i];
	  contents = unity_webapps_script_loader_get_require_contents (self, require_file);

	  if (contents == NULL)
		{
		  g_string_free (combined_requirements, TRUE);
		  return NULL;
		}
	  g_string_append_printf (combined_requirements, "\n// imported script: %s\n", require_file);
	  combined_requirements = g_string_append (combined_requirements, contents);

	  g_free (contents);
	}

  ret = combined_requirements->str;
  g_string_free (combined_requirements, FALSE);

  return ret;
}

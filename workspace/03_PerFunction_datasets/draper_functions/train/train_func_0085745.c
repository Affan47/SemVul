parse_data_uri (const gchar *data_uri,
		gchar **mimetype,
		gchar **data)
{
  gchar **split;
  int result;

  g_assert (g_str_has_prefix (data_uri, "data:") == TRUE);

  split = g_strsplit (data_uri+5,
		      ";base64,",
		      2);

  result = g_strv_length (split);

  if (result != 2)
    {
      UNITY_WEBAPPS_NOTE (RESOURCE, "Failed to parse data uri: \n %s \n", data_uri);

      *mimetype = NULL;
      *data = NULL;

      g_strfreev (split);

      return FALSE;
    }

  *mimetype = split[0];
  *data = split[1];

  g_free (split);

  if (g_str_has_prefix (*mimetype, "image/") == FALSE)
    {
      UNITY_WEBAPPS_NOTE (RESOURCE, "Data URI does not have an image mimetype");

      g_free (*data);

      *mimetype = NULL;
      *data = NULL;

      return FALSE;
    }

  return TRUE;
}

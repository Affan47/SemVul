param_list_commas (const struct SdpParam *sdp_param,
    FsCodec *local_codec, FsCodecParameter *local_param,
    FsCodec *remote_codec, FsCodecParameter *remote_param,
    FsCodec *negotiated_codec)
{
  gchar **remote_strv = NULL;
  gchar **local_strv = NULL;
  GString *result = NULL;
  gint i;


  if (!remote_param || !local_param)
    return TRUE;

  remote_strv = g_strsplit (remote_param->value, ",", -1);
  local_strv = g_strsplit (local_param->value, ",", -1);

  for (i = 0; remote_strv[i]; i++)
  {
    gint j;

    for (j = 0; local_strv[j]; j++)
    {
      if (!g_ascii_strcasecmp (remote_strv[i], local_strv[j]))
      {
        if (!result)
          result = g_string_new (remote_strv[i]);
        else
          g_string_append_printf (result, ",%s", remote_strv[i]);
      }
    }
  }

  if (result)
  {
    fs_codec_add_optional_parameter (negotiated_codec, remote_param->name,
        result->str);
    g_string_free (result, TRUE);
  }

  g_strfreev (remote_strv);
  g_strfreev (local_strv);

  return TRUE;
}

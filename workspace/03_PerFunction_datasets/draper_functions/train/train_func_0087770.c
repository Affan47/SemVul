_get_extension (const gchar * uri)
{
  gchar *result;
  gsize len;
  gint find;

  GST_DEBUG ("finding extension of %s", uri);

  if (uri == NULL)
    goto no_uri;


  len = strlen (uri);
  find = len - 1;

  while (find >= 0) {
    if (uri[find] == '.')
      break;
    find--;
  }
  if (find < 0)
    goto no_extension;

  result = g_strdup (&uri[find + 1]);

  GST_DEBUG ("found extension %s", result);

  return result;


no_uri:
  {
    GST_WARNING ("could not parse the peer uri");
    return NULL;
  }
no_extension:
  {
    GST_WARNING ("could not find uri extension in %s", uri);
    return NULL;
  }
}

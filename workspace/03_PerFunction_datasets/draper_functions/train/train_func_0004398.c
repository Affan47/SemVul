validate_mime_str (const gchar *in)
{
  gchar *out = NULL, **it;

  if (!in)
    return NULL;

  gchar **mimes = g_strsplit (in, ";", -1);
  GList *registered = g_content_types_get_registered ();

  for (it = mimes; it && *it; it++)
    {
      if (g_list_find_custom (registered, *it, (GCompareFunc)g_strcmp0))
	{
	  gchar *tmp = g_strconcat (*it, ";", out, NULL);
	  g_free (out);
	  out = tmp;
	}
    }
  g_list_free_full (registered, g_free);
  g_strfreev (mimes);

  return out;
}

create_pixbuf                          (const gchar     *filename)
{
  gchar *pathname = NULL;
  GdkPixbuf *pixbuf;
  GError *error = NULL;

  if (!filename || !filename[0])
	return NULL;

  pathname = NULL;

  if (!pathname)
    {
	  GString *str;
	  str = g_string_new(PACKAGE_PIXMAPS_DIR);
	  g_string_append(str, "/");
	  g_string_append(str, filename);
	  pathname = g_strdup(str->str);
	  g_string_free(str, TRUE);
    }

  pixbuf = gdk_pixbuf_new_from_file (pathname, &error);
  if (!pixbuf)
    {
	  GString *str;
          error = NULL;
          pathname = NULL;
          str = g_string_new("pixmaps/");
          g_string_append(str, filename);
          pathname = g_strdup(str->str);
          g_string_free(str, TRUE);
          pixbuf = gdk_pixbuf_new_from_file (pathname, &error);
    }
  if (!pixbuf)
    {
      fprintf (stderr, "Failed to load pixbuf file: %s: %s\n",
               pathname, error->message);
      g_error_free (error);
    }
  g_free (pathname);
  return pixbuf;
}

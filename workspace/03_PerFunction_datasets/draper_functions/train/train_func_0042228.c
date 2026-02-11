tpaw_pixbuf_from_data_and_mime (gchar *data,
           gsize data_size,
           gchar **mime_type)
{
  GdkPixbufLoader *loader;
  GdkPixbufFormat *format;
  GdkPixbuf *pixbuf = NULL;
  gchar **mime_types;
  GError *error = NULL;

  if (!data)
    return NULL;

  loader = gdk_pixbuf_loader_new ();
  if (!gdk_pixbuf_loader_write (loader, (guchar *) data, data_size, &error))
    {
      DEBUG ("Failed to write to pixbuf loader: %s",
        error ? error->message : "No error given");
      goto out;
    }

  if (!gdk_pixbuf_loader_close (loader, &error))
    {
      DEBUG ("Failed to close pixbuf loader: %s",
        error ? error->message : "No error given");
      goto out;
    }

  pixbuf = gdk_pixbuf_loader_get_pixbuf (loader);
  if (pixbuf)
    {
      g_object_ref (pixbuf);

      if (mime_type != NULL)
        {
          format = gdk_pixbuf_loader_get_format (loader);
          mime_types = gdk_pixbuf_format_get_mime_types (format);

          *mime_type = g_strdup (*mime_types);
          if (mime_types[1] != NULL)
            DEBUG ("Loader supports more than one mime "
              "type! Picking the first one, %s",
              *mime_type);

          g_strfreev (mime_types);
        }
    }

out:
  g_clear_error (&error);
  g_object_unref (loader);

  return pixbuf;
}

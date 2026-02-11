preview_image_from_data_uri (const gchar *data_uri)
{
  GdkPixbufLoader *loader;
  GdkPixbuf *pixbuf, *unscaled_pixbuf;
  gchar *mimetype, *data;
  guchar *decoded;
  gsize decoded_length;
  gboolean parsed, wrote;
  GError *error;

  mimetype = NULL;
  data = NULL;

  pixbuf = NULL;
  loader = NULL;

  parsed = parse_data_uri (data_uri, &mimetype, &data);

  if (parsed == FALSE)
	{
	  g_warning ("Failed to parse data uri");
	  return NULL;
	}

  decoded = g_base64_decode (data, &decoded_length);

  g_assert (decoded != NULL);

  loader = gdk_pixbuf_loader_new ();

  error = NULL;
  wrote = gdk_pixbuf_loader_write (loader, decoded,
								   decoded_length,
								   &error);
  if (wrote == FALSE)
	{
	  if (error == NULL)
		{
		  goto out;
		}
	  g_warning ("Failed to write data to GdkPixbuf: %s", error->message);
	  g_error_free (error);

	  goto out;
	}

  printf("Wrote %zu bytes\n", decoded_length);

  error = NULL;

  if (error != NULL)
	{
	  g_warning("Failed to close pixbuf loader: %s", error->message);
	  g_error_free (error);

	  goto out;
	}

  unscaled_pixbuf = gdk_pixbuf_loader_get_pixbuf (loader);

  pixbuf = scale_preview_pixbuf (unscaled_pixbuf);

  g_object_unref (G_OBJECT (unscaled_pixbuf));

  gdk_pixbuf_loader_close (loader, NULL);


 out:
  if (loader != NULL)
	{
	  g_object_unref (G_OBJECT (loader));
	}
  g_free (mimetype);
  g_free (data);
  g_free (decoded);

  return pixbuf;
}

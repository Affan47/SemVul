icns_image_load (FILE *f, GError ** error)
{
  GByteArray *data;
  GdkPixbuf *pixbuf = NULL;
  guint i;

  data = g_byte_array_new ();
  while (!feof (f))
    {
      gint save_errno;
      guchar buf[4096];
      gsize bytes;

      bytes = fread (buf, 1, sizeof (buf), f);
      save_errno = errno;
      data = g_byte_array_append (data, buf, bytes);

      if (ferror (f))
        {
	  g_set_error (error,
		       G_FILE_ERROR,
		       g_file_error_from_errno (save_errno),
		       _("Error reading ICNS image: %s"),
		       g_strerror (save_errno));

	  g_byte_array_free (data, TRUE);

	  return NULL;
	}
    }

  for (i = 0; i < G_N_ELEMENTS(sizes) && !pixbuf; i++)
    pixbuf = load_icon (sizes[i], data->data, data->len);

  g_byte_array_free (data, TRUE);

  if (!pixbuf)
    g_set_error_literal (error, GDK_PIXBUF_ERROR,
                         GDK_PIXBUF_ERROR_CORRUPT_IMAGE,
                         _("Could not decode ICNS file"));

  return pixbuf;
}

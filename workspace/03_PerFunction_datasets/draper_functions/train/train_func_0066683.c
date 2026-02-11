create_loader (GFile        *file,
               const guchar *data,
               gsize         size)
{
  GdkPixbufLoader *loader;
  GError *error = NULL;
  char *mime_type;
  char *filename;

  loader = NULL;


  filename = g_file_get_basename (file);
  mime_type = g_content_type_guess (filename, data, size, NULL);
  g_free (filename);

  if (mime_type != NULL) {
    loader = gdk_pixbuf_loader_new_with_mime_type (mime_type, &error);
  }

  if (loader == NULL) {
    g_warning ("Unable to create loader for mime type %s: %s", mime_type, error->message);
    g_clear_error (&error);
    loader = gdk_pixbuf_loader_new ();
  }
  g_free (mime_type);

  return loader;
}

_write_photo (PhotoData *data)
{
#ifdef HAVE_GNOME3
  cairo_surface_t *surface;
  cairo_status_t   status;

  surface = gtk_offscreen_window_get_surface (GTK_OFFSCREEN_WINDOW (data->window));
  status = cairo_surface_write_to_png (surface, data->outfile);

  switch (status) {
    case CAIRO_STATUS_SUCCESS:
      break;
    default:
      data->error = TRUE;

      g_printerr (_("Error while saving '%s': %s\n"),
                  data->uri, cairo_status_to_string (status));
      break;
  }
#else
  GdkPixbuf *pixbuf;
  GError    *error = NULL;

  pixbuf = gtk_offscreen_window_get_pixbuf (GTK_OFFSCREEN_WINDOW (data->window));
  gdk_pixbuf_save (pixbuf, data->outfile, "png", &error, NULL);
  g_object_unref (pixbuf);

  if (error) {
    data->error = TRUE;

    g_printerr (_("Error while saving '%s': %s\n"),
                data->uri, error->message);
    g_error_free (error);
  }
#endif
}

save_pixbuf_ready_cb (GObject *source,
                      GAsyncResult *res,
                      gpointer user_data)
{
  GError *error = NULL;
  ScreenshotApplication *self = user_data;

  gdk_pixbuf_save_to_stream_finish (res, &error);

  if (error != NULL)
    {
      save_pixbuf_handle_error (self, error);
      g_error_free (error);
      return;
    }

  save_pixbuf_handle_success (self);
}

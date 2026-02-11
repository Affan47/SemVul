on_window_key_press_event (GtkWidget *widget, GdkEventKey *event)
{
  if (event->keyval == GDK_KEY_F12)
    {
      GdkPixbuf *pix = gdk_pixbuf_get_from_window (gtk_widget_get_window (widget), 0, 0,
                                                   gtk_widget_get_allocated_width (widget),
                                                   gtk_widget_get_allocated_height (widget));
      gchar tmp_file[] = "glade-screenshot-XXXXXX.png";

      g_mkstemp (tmp_file);
      gdk_pixbuf_save (pix, tmp_file, "png", NULL, NULL);
      g_object_unref (pix);
      return TRUE;
    }

  return FALSE;
}

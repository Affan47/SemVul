kkam_internal_viewer (char *filename)
{
  GtkWidget *ebox;
  GdkPixmap *pix = NULL;
  GdkBitmap *bit = NULL;
  ViewerInfo *vi;

  vi = g_new0 (ViewerInfo, 1);
  if ((vi->pixbuf = gdk_pixbuf_new_from_file (filename, NULL)) == NULL)
  {
    g_free (vi);
    return;
  }

  vi->fdialog = NULL;
  kkam_iv_makemenu (vi);
  vi->window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (vi->window), filename);
  g_signal_connect_swapped (G_OBJECT (vi->window), "delete_event",
                             G_CALLBACK (kkam_iv_destroy),
                             (gpointer)vi);
  g_signal_connect_swapped (G_OBJECT (vi->window), "configure_event",
                             G_CALLBACK (kkam_iv_resize),
                             (gpointer)vi);

  gtk_window_set_wmclass (GTK_WINDOW (vi->window), "KKamViewer", "GKrellm");

  gkrellm_scale_pixbuf_to_pixmap(vi->pixbuf, &pix, &bit,
                      gdk_pixbuf_get_width(vi->pixbuf),
                      gdk_pixbuf_get_height(vi->pixbuf));

  vi->pmap = gtk_image_new_from_pixmap(pix, bit);
  g_object_unref(G_OBJECT(pix));
  if (bit)
    g_object_unref(G_OBJECT(bit));

  ebox = gtk_event_box_new ();
  gtk_container_add (GTK_CONTAINER (ebox), vi->pmap);
  gtk_container_add (GTK_CONTAINER (vi->window), ebox);
  gtk_widget_set_events (ebox, GDK_BUTTON_PRESS_MASK);
  g_signal_connect_swapped (G_OBJECT (ebox), "button_press_event",
                             G_CALLBACK (kkam_iv_popup), (gpointer)vi);
  gtk_widget_show_all (vi->window);
}

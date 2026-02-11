get_visualization_size (BaconVideoWidget *bvw,
                        int *w, int *h, gint *fps_n, gint *fps_d)
{
  GdkScreen *screen;
  int new_fps_n;

  g_return_if_fail (h != NULL);
  g_return_if_fail (bvw->priv->visq < G_N_ELEMENTS (vis_qualities));

  if (gtk_widget_get_realized (GTK_WIDGET (bvw)) == FALSE) {
    if (fps_n)
      *fps_n = 1;
    if (fps_d)
      *fps_d = 1;
    return;
  }

  *h = vis_qualities[bvw->priv->visq].height;
  new_fps_n = vis_qualities[bvw->priv->visq].fps;

  screen = gtk_widget_get_screen (GTK_WIDGET (bvw));
  *w = *h * gdk_screen_get_width (screen) / gdk_screen_get_height (screen);

  if (fps_n)
    *fps_n = new_fps_n;
  if (fps_d)
    *fps_d = 1;
}

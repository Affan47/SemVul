configure_event_callback (GtkWidget * widget, GdkEventConfigure * event)
{
  if (ball_surface)
    cairo_surface_destroy(ball_surface);

  if (blank_surface)
    cairo_surface_destroy (blank_surface);

  boxsize = (event->width - 1) / hfieldsize;
  ball_surface = gdk_window_create_similar_surface (gtk_widget_get_window (draw_area),
                                                    CAIRO_CONTENT_COLOR_ALPHA,
                                                    boxsize * 4, boxsize * 7);
  blank_surface = gdk_window_create_similar_surface (gtk_widget_get_window (draw_area),
                                                     CAIRO_CONTENT_COLOR_ALPHA,
                                                     boxsize, boxsize);
  refresh_pixmaps ();

  refresh_screen ();

  return TRUE;
}

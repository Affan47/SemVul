gtk_plot_gdk_draw_rectangle                          (GtkPlotPC *pc,
                                                     gint filled,
                                                     gdouble x, gdouble y,
                                                     gdouble width, gdouble height)
{
  if(!GTK_PLOT_GDK(pc)->gc) return;
  if(!GTK_PLOT_GDK(pc)->drawable) return;

  gdk_draw_rectangle (GTK_PLOT_GDK(pc)->drawable, GTK_PLOT_GDK(pc)->gc,
                      filled,
                      roundint(x), roundint(y),
                      roundint(width), roundint(height));

}

gabedit_xyplot_set_background_color (GabeditXYPlot *xyplot, GdkColor color)
{
  g_return_if_fail (xyplot != NULL);
  g_return_if_fail (GABEDIT_IS_XYPLOT (xyplot));

  gdk_gc_set_rgb_fg_color(xyplot->back_gc, &color);

  gtk_widget_queue_draw(GTK_WIDGET(xyplot));
}

gd_header_bar_map (GtkWidget *widget)
{
  GdHeaderBar *bar = GD_HEADER_BAR (widget);
  GdHeaderBarPrivate *priv = bar->priv;

  GTK_WIDGET_CLASS (gd_header_bar_parent_class)->map (widget);

  if (priv->event_window)
    gdk_window_show_unraised (priv->event_window);
}

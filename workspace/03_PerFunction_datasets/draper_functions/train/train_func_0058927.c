glade_gtk_grid_replace_child (GladeWidgetAdaptor *adaptor,
                              GObject            *container,
                              GObject            *current,
                              GObject            *new_widget)
{
  g_return_if_fail (GTK_IS_GRID (container));
  g_return_if_fail (GTK_IS_WIDGET (current));
  g_return_if_fail (GTK_IS_WIDGET (new_widget));


  GWA_GET_CLASS (GTK_TYPE_CONTAINER)->replace_child (adaptor,
                                                     container,
                                                     current,
                                                     new_widget);


  if (!GLADE_IS_PLACEHOLDER (new_widget))
    glade_gtk_grid_refresh_placeholders (GTK_GRID (container), FALSE);
}

get_drop_window (GtkWidget * widget)
{
  GtkWidget *target_window;

  target_window = gtk_widget_get_toplevel (widget);
  g_return_val_if_fail (GTR_IS_WINDOW (target_window), NULL);

  return GTR_WINDOW (target_window);
}

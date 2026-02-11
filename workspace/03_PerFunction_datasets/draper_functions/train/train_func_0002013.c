goo_canvas_accessible_get_n_children (AtkObject *object)
{
  GtkAccessible *accessible;
  GtkWidget *widget;

  accessible = GTK_ACCESSIBLE (object);
  widget = gtk_accessible_get_widget (accessible);


  if (widget == NULL)
    return 0;

  g_return_val_if_fail (GOO_IS_CANVAS (widget), 0);

  if (goo_canvas_get_root_item (GOO_CANVAS (widget)))
    return 1;

  return 0;
}

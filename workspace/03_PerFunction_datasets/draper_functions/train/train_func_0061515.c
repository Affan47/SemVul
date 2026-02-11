glade_gtk_box_remove_child (GladeWidgetAdaptor * adaptor,
                            GObject * object, GObject * child)
{
  GladeWidget *gbox;
  gint size;

  g_return_if_fail (GTK_IS_BOX (object));
  g_return_if_fail (GTK_IS_WIDGET (child));

  gbox = glade_widget_get_from_gobject (object);

  gtk_container_remove (GTK_CONTAINER (object), GTK_WIDGET (child));

  if (glade_widget_superuser () == FALSE)
    {
      glade_widget_property_get (gbox, "size", &size);
      glade_widget_property_set (gbox, "size", size);
    }

  fix_response_id_on_child (gbox, child, FALSE);
}

glade_gtk_tool_palette_set_child_property (GladeWidgetAdaptor * adaptor,
					   GObject * container,
					   GObject * child,
					   const gchar * property_name,
					   GValue * value)
{
  g_return_if_fail (GTK_IS_TOOL_PALETTE (container));
  g_return_if_fail (GTK_IS_TOOL_ITEM_GROUP (child));

  g_return_if_fail (property_name != NULL || value != NULL);

  if (strcmp (property_name, "position") == 0)
    {
      GtkToolPalette *palette = GTK_TOOL_PALETTE (container);
      GList *children;
      gint position, size;

      children = glade_util_container_get_all_children (GTK_CONTAINER (palette));
      size = g_list_length (children);
      g_list_free (children);

      position = g_value_get_int (value);

      if (position >= size)
        position = size - 1;

      gtk_tool_palette_set_group_position (palette, GTK_TOOL_ITEM_GROUP (child), position);
    }
  else

    GWA_GET_CLASS
        (GTK_TYPE_CONTAINER)->child_set_property (adaptor,
                                                  container, child,
                                                  property_name, value);
}

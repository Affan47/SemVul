glade_gtk_treeview_set_child_property (GladeWidgetAdaptor * adaptor,
                                       GObject * container,
                                       GObject * child,
                                       const gchar * property_name,
                                       const GValue * value)
{
  if (strcmp (property_name, "position") == 0)
    {

      gtk_tree_view_remove_column (GTK_TREE_VIEW (container),
                                   GTK_TREE_VIEW_COLUMN (child));
      gtk_tree_view_insert_column (GTK_TREE_VIEW (container),
                                   GTK_TREE_VIEW_COLUMN (child),
                                   g_value_get_int (value));
    }
  else

    GWA_GET_CLASS
        (GTK_TYPE_CONTAINER)->child_set_property (adaptor,
                                                  container, child,
                                                  property_name, value);
}

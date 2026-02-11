exo_wrap_table_add (GtkContainer *container,
                    GtkWidget    *widget)
{
  ExoWrapTable *table = EXO_WRAP_TABLE (container);


  gtk_widget_set_parent (widget, GTK_WIDGET (table));


  table->priv->children = g_list_append (table->priv->children, widget);


  if (GTK_WIDGET_REALIZED (container))
    gtk_widget_realize (widget);


  if (GTK_WIDGET_VISIBLE (container) && GTK_WIDGET_VISIBLE (widget))
    {
      if (GTK_WIDGET_MAPPED (container))
        gtk_widget_map (widget);
    }


  gtk_widget_queue_resize (GTK_WIDGET (container));
}

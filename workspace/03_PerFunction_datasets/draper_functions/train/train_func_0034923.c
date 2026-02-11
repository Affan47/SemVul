append_item (GladeEditorTable * table,
             GladePropertyClass * klass, gboolean from_query_dialog)
{
  GladeEditorProperty *property;
  GtkWidget *label;

  if (!(property = glade_widget_adaptor_create_eprop
        (glade_property_class_get_adaptor (klass), klass, from_query_dialog == FALSE)))
    {
      g_critical ("Unable to create editor for property '%s' of class '%s'",
                  glade_property_class_id (klass),
		  glade_widget_adaptor_get_name (glade_property_class_get_adaptor (klass)));
      return NULL;
    }

  gtk_widget_show (GTK_WIDGET (property));
  gtk_widget_show_all (glade_editor_property_get_item_label (property));

  label = glade_editor_property_get_item_label (property);
  gtk_widget_set_hexpand (label, FALSE);

  glade_editor_table_attach (table, label, 0, table->priv->rows);
  glade_editor_table_attach (table, GTK_WIDGET (property), 1, table->priv->rows);

  table->priv->rows++;

  return property;
}

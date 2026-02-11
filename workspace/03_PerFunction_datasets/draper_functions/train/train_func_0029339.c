update_editor_sheet (EggToolbarEditor *editor)
{
  GList *l;
  GList *to_drag;
  int x, y, height, width;
  GtkWidget *table;
  GtkWidget *viewport;
  GtkWidget *item;
  GtkWidget *icon;

  g_return_if_fail (EGG_IS_TOOLBAR_EDITOR (editor));

  viewport = GTK_BIN (editor->priv->scrolled_window)->child;
  if (viewport)
    {
      table = GTK_BIN (viewport)->child;
      gtk_container_remove (GTK_CONTAINER (viewport), table);
    }
  table = gtk_table_new (0, 0, TRUE);
  editor->priv->table = table;
  gtk_container_set_border_width (GTK_CONTAINER (table), 12);
  gtk_widget_show (table);
  gtk_scrolled_window_add_with_viewport
    (GTK_SCROLLED_WINDOW (editor->priv->scrolled_window), table);
  gtk_drag_dest_set (table, GTK_DEST_DEFAULT_ALL,
		     dest_drag_types, n_dest_drag_types, GDK_ACTION_MOVE);
  g_signal_connect (table, "drag_data_received",
		    G_CALLBACK (editor_drag_data_received_cb), editor);

  to_drag = editor->priv->actions_list;

  x = y = 0;
  width = 3;
  height = (g_list_length (to_drag)) / width + 1;
  gtk_table_resize (GTK_TABLE (editor->priv->table), height, width);

  for (l = to_drag; l != NULL; l = l->next)
    {
      GtkAction *action = (l->data);
      const char *stock_id, *short_label;
      GValue value = { 0, };

      g_value_init (&value, G_TYPE_STRING);
      g_object_get_property (G_OBJECT (action), "stock_id", &value);
      stock_id = g_value_get_string (&value);
      icon = gtk_image_new_from_stock
		(stock_id ? stock_id : GTK_STOCK_DND,
		 GTK_ICON_SIZE_LARGE_TOOLBAR);
      g_value_unset (&value);

      g_value_init (&value, G_TYPE_STRING);
      g_object_get_property (G_OBJECT (action), "short_label", &value);
      short_label = g_value_get_string (&value);
      item = editor_create_item (editor, GTK_IMAGE (icon),
				 short_label, GDK_ACTION_MOVE);
      g_value_unset (&value);
      g_object_set_data (G_OBJECT (item), "egg-action", action);
      gtk_table_attach_defaults (GTK_TABLE (editor->priv->table),
		                 item, x, x + 1, y, y + 1);

      x++;
      if (x >= width)
	{
	  x = 0;
	  y++;
	}
    }

  icon = _egg_editable_toolbar_new_separator_image ();
  item = editor_create_item (editor, GTK_IMAGE (icon), _("Separator"),
			     GDK_ACTION_COPY);
  gtk_table_attach_defaults (GTK_TABLE (editor->priv->table),
		             item, x, x + 1, y, y + 1);
}

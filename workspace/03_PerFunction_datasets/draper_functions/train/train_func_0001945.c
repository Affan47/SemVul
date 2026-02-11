add_actions (GladeWindow *window, GladeWidget *widget, GList *actions)
{
  GtkToolbar *bar = GTK_TOOLBAR (window->priv->toolbar);
  GtkToolItem *item = gtk_separator_tool_item_new ();
  gint n = 0;
  GList *l;

  gtk_toolbar_insert (bar, item, -1);
  gtk_widget_show (GTK_WIDGET (item));

  if (window->priv->actions_start == 0)
    window->priv->actions_start = gtk_toolbar_get_item_index (bar, item);

  for (l = actions; l; l = g_list_next (l))
    {
      GladeWidgetAction *action = l->data;
      GWActionClass     *aclass = glade_widget_action_get_class (action);

      if (!aclass->important || !glade_widget_action_get_visible (action))
        continue;

      if (glade_widget_action_get_children (action))
        {
          g_warning ("Trying to add a group action to the toolbar is unsupported");
          continue;
        }

      item = gtk_tool_button_new_from_stock ((aclass->stock) ? aclass->stock : "gtk-execute");
      if (aclass->label)
	{
	  gtk_tool_button_set_label (GTK_TOOL_BUTTON (item), aclass->label);
	  gtk_widget_set_tooltip_text (GTK_WIDGET (item), aclass->label);
	}

      g_object_set_data (G_OBJECT (item), "glade-widget", widget);


      g_signal_connect_data (item, "clicked",
                             G_CALLBACK (activate_action),
                             action, action_disconnect, 0);

      gtk_widget_set_sensitive (GTK_WIDGET (item),
				glade_widget_action_get_sensitive (action));

      g_signal_connect (action, "notify::sensitive",
                        G_CALLBACK (activate_action), GTK_WIDGET (item));

      gtk_toolbar_insert (bar, item, -1);
      gtk_tool_item_set_homogeneous (item, FALSE);
      gtk_widget_show (GTK_WIDGET (item));
      n++;
    }

  if (n == 0)
    clean_actions (window);
}

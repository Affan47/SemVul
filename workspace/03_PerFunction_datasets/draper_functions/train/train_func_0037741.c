toolbar_append_item (GtkToolbar *toolbar,
					 GtkWidget  *widget,
					 const char *text,
					 const char *private_text,
					 gboolean	 show,

					 const char	*action_name,
					 const char	*stock_id,
					 gpointer	 data)
{
	GtkToolItem *tool_item;

	UT_ASSERT(GTK_IS_TOOLBAR (toolbar));
	UT_ASSERT(widget != NULL);

	if (GTK_IS_TOOL_ITEM (widget)) {
		tool_item = GTK_TOOL_ITEM (widget);
		gtk_tool_item_set_tooltip_text(tool_item, text);
	}
	else {
		tool_item = gtk_tool_item_new ();
		GtkWidget *box = gtk_event_box_new ();
		gtk_container_add (GTK_CONTAINER (tool_item), box);
		gtk_container_add (GTK_CONTAINER (box), widget);
		gtk_tool_item_set_tooltip_text(tool_item, text);
		if (action_name && data) {
			GtkAction	*proxy_action;
			GtkWidget 	*menu_item;
			proxy_action = gtk_action_new (action_name, text, private_text, stock_id);
			g_signal_connect (proxy_action, "activate",
							  G_CALLBACK (s_proxy_activated), data);
			menu_item = gtk_action_create_menu_item (proxy_action);
			gtk_tool_item_set_proxy_menu_item (tool_item, text, menu_item);
			g_object_unref (G_OBJECT (proxy_action));
		}
	}
	gtk_toolbar_insert (toolbar, tool_item, -1);
	if (show) {
		gtk_widget_show_all (GTK_WIDGET (tool_item));
	}

	return GTK_WIDGET (tool_item);
}

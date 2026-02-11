kb_show_popup_menu(GtkWidget *widget, GdkEventButton *event)
{
	GtkWidget *item;
	static GtkWidget *menu = NULL;
	guint button;
	guint32 event_time;

	if (menu == NULL)
	{
		menu = gtk_menu_new();

		item = ui_image_menu_item_new(GTK_STOCK_ADD, _("_Expand All"));
		gtk_widget_show(item);
		gtk_container_add(GTK_CONTAINER(menu), item);
		g_signal_connect(item, "activate", G_CALLBACK(kb_expand_collapse_cb), GINT_TO_POINTER(TRUE));

		item = ui_image_menu_item_new(GTK_STOCK_REMOVE, _("_Collapse All"));
		gtk_widget_show(item);
		gtk_container_add(GTK_CONTAINER(menu), item);
		g_signal_connect(item, "activate", G_CALLBACK(kb_expand_collapse_cb), NULL);

		gtk_menu_attach_to_widget(GTK_MENU(menu), widget, NULL);
	}

	if (event != NULL)
	{
		button = event->button;
		event_time = event->time;
	}
	else
	{
		button = 0;
		event_time = gtk_get_current_event_time();
	}

	gtk_menu_popup(GTK_MENU(menu), NULL, NULL, NULL, NULL, button, event_time);
}

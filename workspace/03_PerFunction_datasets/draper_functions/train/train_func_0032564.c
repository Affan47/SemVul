show_tab_bar_popup_menu(GdkEventButton *event, GtkWidget *page)
{
	GtkWidget *menu_item;
	static GtkWidget *menu = NULL;
	GeanyDocument *doc = NULL;
	gint page_num;

	if (menu == NULL)
		menu = gtk_menu_new();


	gtk_container_foreach(GTK_CONTAINER(menu), (GtkCallback) gtk_widget_destroy, NULL);

	ui_menu_add_document_items(GTK_MENU(menu), document_get_current(),
		G_CALLBACK(tab_bar_menu_activate_cb));

	menu_item = gtk_separator_menu_item_new();
	gtk_widget_show(menu_item);
	gtk_container_add(GTK_CONTAINER(menu), menu_item);

	if (page != NULL)
	{
		page_num = gtk_notebook_page_num(GTK_NOTEBOOK(main_widgets.notebook), page);
		doc = document_get_from_page(page_num);
	}

	menu_item = ui_image_menu_item_new(GTK_STOCK_OPEN, "Open in New _Window");
	gtk_widget_show(menu_item);
	gtk_container_add(GTK_CONTAINER(menu), menu_item);
	g_signal_connect(menu_item, "activate",
		G_CALLBACK(on_open_in_new_window_activate), doc);

	if (doc == NULL || !doc->real_path)
		gtk_widget_set_sensitive(menu_item, FALSE);

	menu_item = gtk_separator_menu_item_new();
	gtk_widget_show(menu_item);
	gtk_container_add(GTK_CONTAINER(menu), menu_item);

	menu_item = gtk_image_menu_item_new_from_stock(GTK_STOCK_CLOSE, NULL);
	gtk_widget_show(menu_item);
	gtk_container_add(GTK_CONTAINER(menu), menu_item);
	g_signal_connect(menu_item, "activate", G_CALLBACK(notebook_tab_close_clicked_cb), page);
	gtk_widget_set_sensitive(GTK_WIDGET(menu_item), (page != NULL));

	menu_item = ui_image_menu_item_new(GTK_STOCK_CLOSE, _("Close Ot_her Documents"));
	gtk_widget_show(menu_item);
	gtk_container_add(GTK_CONTAINER(menu), menu_item);
	g_signal_connect(menu_item, "activate", G_CALLBACK(on_close_other_documents1_activate), page);
	gtk_widget_set_sensitive(GTK_WIDGET(menu_item), (page != NULL));

	menu_item = ui_image_menu_item_new(GTK_STOCK_CLOSE, _("C_lose All"));
	gtk_widget_show(menu_item);
	gtk_container_add(GTK_CONTAINER(menu), menu_item);
	g_signal_connect(menu_item, "activate", G_CALLBACK(on_close_all1_activate), NULL);

	gtk_menu_popup(GTK_MENU(menu), NULL, NULL, NULL, NULL, event->button, event->time);
}

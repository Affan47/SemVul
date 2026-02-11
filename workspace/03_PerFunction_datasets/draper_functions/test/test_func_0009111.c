create_tree_popup_menu (BraseroPluginManagerUI *pm)
{
	GtkWidget *menu;
	GtkWidget *item;
	GtkWidget *image;
	BraseroPlugin *plugin;

	plugin = plugin_manager_ui_get_selected_plugin (pm);

	if (!plugin)
		return NULL;

	menu = gtk_menu_new ();

	item = gtk_image_menu_item_new_with_mnemonic (_("_About"));
	image = gtk_image_new_from_stock (GTK_STOCK_ABOUT,
					  GTK_ICON_SIZE_MENU);
	gtk_image_menu_item_set_image (GTK_IMAGE_MENU_ITEM (item), image);
	g_signal_connect (item, "activate",
			  G_CALLBACK (about_button_cb), pm);
	gtk_menu_shell_append (GTK_MENU_SHELL (menu), item);

	item = gtk_image_menu_item_new_with_mnemonic (_("C_onfigure"));
	image = gtk_image_new_from_stock (GTK_STOCK_PREFERENCES,
					  GTK_ICON_SIZE_MENU);
	gtk_image_menu_item_set_image (GTK_IMAGE_MENU_ITEM (item), image);
	g_signal_connect (item, "activate",
			  G_CALLBACK (configure_button_cb), pm);
	gtk_widget_set_sensitive (item,
				  (brasero_plugin_get_next_conf_option (plugin, NULL) != NULL));
	gtk_menu_shell_append (GTK_MENU_SHELL (menu), item);

	item = gtk_check_menu_item_new_with_mnemonic (_("A_ctivate"));
	gtk_widget_set_sensitive (item,
				  brasero_plugin_get_gtype (plugin) != G_TYPE_NONE && !brasero_plugin_get_compulsory (plugin));
	gtk_check_menu_item_set_active (GTK_CHECK_MENU_ITEM (item),
					brasero_plugin_get_active (plugin, 0));
	g_signal_connect (item, "toggled",
			  G_CALLBACK (enable_plugin_menu_cb), pm);
	gtk_menu_shell_append (GTK_MENU_SHELL (menu), item);

	item = gtk_separator_menu_item_new ();
	gtk_menu_shell_append (GTK_MENU_SHELL (menu), item);

	item = gtk_menu_item_new_with_mnemonic (_("Ac_tivate All"));
	g_signal_connect (item, "activate",
			  G_CALLBACK (enable_all_menu_cb), pm);
	gtk_menu_shell_append (GTK_MENU_SHELL (menu), item);

	item = gtk_menu_item_new_with_mnemonic (_("_Deactivate All"));
	g_signal_connect (item, "activate",
			  G_CALLBACK (disable_all_menu_cb), pm);
	gtk_menu_shell_append (GTK_MENU_SHELL (menu), item);

	gtk_widget_show_all (menu);

	return menu;
}

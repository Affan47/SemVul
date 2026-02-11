eb_import_window(void *v_import_submenuitem)
{
	GtkWidget *import_submenuitem = v_import_submenuitem;
	GtkWidget *label;
	LList *list = NULL;
	GtkWidget *import_menu = gtk_menu_new();
	menu_data *md = NULL;
	menu_item_data *mid = NULL;

	label = gtk_tearoff_menu_item_new();
	gtk_menu_shell_append(GTK_MENU_SHELL(import_menu), label);
	gtk_widget_show(label);

	if ((md = GetPref(EB_IMPORT_MENU))) {
		for (list = md->menu_items; list; list = list->next) {
			mid = (menu_item_data *)list->data;
			eb_debug(DBG_CORE, "adding import item: %s\n",
				mid->label);
			label = gtk_menu_item_new_with_label(mid->label);
			gtk_menu_shell_append(GTK_MENU_SHELL(import_menu),
				label);
			g_signal_connect(label, "activate",
				G_CALLBACK(eb_import_function), mid);
			gtk_widget_show(label);
		}
	}
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(import_submenuitem),
		import_menu);
	gtk_widget_show(import_menu);
	gtk_widget_show(import_submenuitem);
}

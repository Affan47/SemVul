main_window_reflect_tags_changes_real(gpointer data)
{
	GtkMenuShell *menu;
	GList *children, *cur;
	MainWindow *mainwin = (MainWindow *)data;

	if (summary_is_locked(mainwin->summaryview)) {
		tags_tag = 0;
		return TRUE;
	}

	menu = GTK_MENU_SHELL(mainwin->tags_menu);
	cm_return_val_if_fail(menu != NULL, FALSE);


	children = gtk_container_get_children(GTK_CONTAINER(menu));
	for (cur = children; cur != NULL && cur->data != NULL; cur = cur->next) {
		gtk_menu_item_set_submenu(GTK_MENU_ITEM(cur->data), NULL);
	}
	g_list_free(children);
	mainwindow_tags_menu_create(mainwin, TRUE);
	summary_reflect_tags_changes(mainwin->summaryview);

	tags_tag = 0;
	return FALSE;
}

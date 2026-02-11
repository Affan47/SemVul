column_header_menu_toggled (GtkCheckMenuItem *menu_item,
                            NautilusListView *list_view)
{
	NautilusFile *file;
	char **visible_columns;
	char **column_order;
	const char *column;
	GList *list = NULL;
	GList *l;
	int i;

	file = nautilus_view_get_directory_as_file (NAUTILUS_VIEW (list_view));
	visible_columns = get_visible_columns (list_view);
	column_order = get_column_order (list_view);
	column = g_object_get_data (G_OBJECT (menu_item), "column-name");

	for (i = 0; visible_columns[i] != NULL; ++i) {
		list = g_list_prepend (list, visible_columns[i]);
	}

	if (gtk_check_menu_item_get_active (menu_item)) {
		list = g_list_prepend (list, g_strdup (column));
	} else {
		l = g_list_find_custom (list, column, (GCompareFunc) g_strcmp0);
		list = g_list_delete_link (list, l);
	}

	list = g_list_reverse (list);
	nautilus_file_set_metadata_list (file,
	                                 NAUTILUS_METADATA_KEY_LIST_VIEW_VISIBLE_COLUMNS,
	                                 list);

	g_free (visible_columns);

	visible_columns = g_new0 (char *, g_list_length (list) + 1);
	for (i = 0, l = list; l != NULL; ++i, l = l->next) {
		visible_columns[i] = l->data;
	}


	apply_columns_settings (list_view, column_order, visible_columns);

	g_list_free (list);
	g_strfreev (column_order);
	g_strfreev (visible_columns);
}

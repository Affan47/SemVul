panel_addto_populate_application_model (GtkTreeStore *store,
					GtkTreeIter  *parent,
					GSList       *app_list)
{
	PanelAddtoAppList *data;
	GtkTreeIter        iter;
	char              *text;
	GSList            *app;

	for (app = app_list; app != NULL; app = app->next) {
		data = app->data;
		gtk_tree_store_append (store, &iter, parent);

		text = panel_addto_make_text (data->item_info.name,
					      data->item_info.description);
		gtk_tree_store_set (store, &iter,
				    COLUMN_ICON, data->item_info.icon,
				    COLUMN_TEXT, text,
				    COLUMN_DATA, &(data->item_info),
				    COLUMN_SEARCH, data->item_info.name,
				    -1);

		g_free (text);

		if (data->children != NULL)
			panel_addto_populate_application_model (store,
								&iter,
								data->children);
	}
}

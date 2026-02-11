theme_create_model(void)
	{
	GtkListStore	*store;
	GtkTreeIter		iter;
	GList			*list;
	Theme			*theme;

	gkrellm_make_themes_list();
	store = gtk_list_store_new(N_THEME_COLUMNS, G_TYPE_STRING, G_TYPE_STRING);
	for (list = themes_list; list; list = list->next)
		{
		theme = (Theme *) list->data;
		gtk_list_store_append(store, &iter);
		gtk_list_store_set(store, &iter,
				THEME_COLUMN, theme->name,
				PATH_COLUMN, theme->path,
				-1);
		}
	return GTK_TREE_MODEL(store);
	}

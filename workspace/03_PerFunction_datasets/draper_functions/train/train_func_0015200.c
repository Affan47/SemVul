vflist_new(ViewFile *vf, FileData *dir_fd)
{
	GtkTreeStore *store;
	GtkTreeSelection *selection;
	GType flist_types[FILE_COLUMN_COUNT];
	gint i;
	gint column;

	vf->info = g_new0(ViewFileInfoList, 1);

	flist_types[FILE_COLUMN_POINTER] = G_TYPE_POINTER;
	flist_types[FILE_COLUMN_VERSION] = G_TYPE_INT;
	flist_types[FILE_COLUMN_THUMB] = GDK_TYPE_PIXBUF;
	flist_types[FILE_COLUMN_FORMATTED] = G_TYPE_STRING;
	flist_types[FILE_COLUMN_NAME] = G_TYPE_STRING;
	flist_types[FILE_COLUMN_SIDECARS] = G_TYPE_STRING;
	flist_types[FILE_COLUMN_SIZE] = G_TYPE_STRING;
	flist_types[FILE_COLUMN_DATE] = G_TYPE_STRING;
	flist_types[FILE_COLUMN_EXPANDED] = G_TYPE_BOOLEAN;
	flist_types[FILE_COLUMN_COLOR] = G_TYPE_BOOLEAN;
	for (i = FILE_COLUMN_MARKS; i < FILE_COLUMN_MARKS + FILEDATA_MARKS_SIZE; i++)
		flist_types[i] = G_TYPE_BOOLEAN;

	store = gtk_tree_store_newv(FILE_COLUMN_COUNT, flist_types);

	vf->listview = gtk_tree_view_new_with_model(GTK_TREE_MODEL(store));
	g_object_unref(store);

	g_signal_connect(G_OBJECT(vf->listview), "row-expanded",
			 G_CALLBACK(vflist_expand_cb), vf);

	g_signal_connect(G_OBJECT(vf->listview), "row-collapsed",
			 G_CALLBACK(vflist_collapse_cb), vf);

	selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(vf->listview));
	gtk_tree_selection_set_mode(GTK_TREE_SELECTION(selection), GTK_SELECTION_MULTIPLE);
	gtk_tree_selection_set_select_function(selection, vflist_select_cb, vf, NULL);

	gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(vf->listview), FALSE);
	gtk_tree_view_set_enable_search(GTK_TREE_VIEW(vf->listview), FALSE);

	column = 0;

	for (i = 0; i < FILEDATA_MARKS_SIZE; i++)
		{
		vflist_listview_add_column_toggle(vf, i + FILE_COLUMN_MARKS, "");
		g_assert(column == FILE_VIEW_COLUMN_MARKS + i);
		column++;
		}

	vflist_listview_add_column(vf, FILE_COLUMN_THUMB, "", TRUE, FALSE, FALSE);
	g_assert(column == FILE_VIEW_COLUMN_THUMB);
	column++;

	vflist_listview_add_column(vf, FILE_COLUMN_FORMATTED, _("Name"), FALSE, FALSE, TRUE);
	g_assert(column == FILE_VIEW_COLUMN_FORMATTED);
	column++;

	vflist_listview_add_column(vf, FILE_COLUMN_SIZE, _("Size"), FALSE, TRUE, FALSE);
	g_assert(column == FILE_VIEW_COLUMN_SIZE);
	column++;

	vflist_listview_add_column(vf, FILE_COLUMN_DATE, _("Date"), FALSE, TRUE, FALSE);
	g_assert(column == FILE_VIEW_COLUMN_DATE);
	column++;

	file_data_register_notify_func(vf_notify_cb, vf, NOTIFY_PRIORITY_MEDIUM);
	return vf;
}

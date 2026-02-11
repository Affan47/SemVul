icon_data_func (GtkTreeViewColumn *column,
                GtkCellRenderer   *renderer,
                GtkTreeModel      *model,
                GtkTreeIter       *iter,
                GitgCommitView    *view)
{
	GitgChangedFile *file;

	gtk_tree_model_get (model, iter, COLUMN_FILE, &file, -1);
	GitgChangedFileStatus status = gitg_changed_file_get_status (file);

	gboolean staged = (model == GTK_TREE_MODEL (view->priv->store_staged));

	switch (status)
	{
		case GITG_CHANGED_FILE_STATUS_NEW:
			g_object_set (renderer,
			              "stock-id",
			              staged ? GTK_STOCK_ADD : GTK_STOCK_NEW,
			              NULL);
		break;
		case GITG_CHANGED_FILE_STATUS_MODIFIED:
			g_object_set (renderer,
			              "stock-id",
			              staged ? GTK_STOCK_APPLY : GTK_STOCK_EDIT,
			              NULL);
		break;
		case GITG_CHANGED_FILE_STATUS_DELETED:
			g_object_set (renderer,
			              "stock-id",
			              staged ? GTK_STOCK_REMOVE : GTK_STOCK_DELETE,
			              NULL);
		break;
		default:
		break;
	}

	g_object_unref (file);
}

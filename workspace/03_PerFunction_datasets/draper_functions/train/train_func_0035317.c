store_row_inserted (GeditFileBrowserStore *store,
		    GtkTreePath		  *path,
		    GtkTreeIter           *iter,
		    MessageCacheData      *data)
{
	guint flags = 0;

	gtk_tree_model_get (GTK_TREE_MODEL (store), iter,
			    GEDIT_FILE_BROWSER_STORE_COLUMN_FLAGS, &flags,
			    -1);

	if (!FILE_IS_DUMMY (flags) && !FILE_IS_FILTERED (flags))
	{
		WindowData *wdata = get_window_data (data->window);

		set_item_message (wdata, iter, path, data->message);
		gedit_message_bus_send_message_sync (wdata->bus, data->message);
	}
}

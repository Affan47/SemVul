search_result_thumb_step(SearchData *sd)
{
	GtkTreeModel *store;
	GtkTreeIter iter;
	MatchFileData *mfd = NULL;
	gboolean valid;
	gint row = 0;
	gint length = 0;

	store = gtk_tree_view_get_model(GTK_TREE_VIEW(sd->result_view));
	valid = gtk_tree_model_get_iter_first(store, &iter);
	if (!sd->thumb_enable)
		{
		while (valid)
			{
			gtk_list_store_set(GTK_LIST_STORE(store), &iter, SEARCH_COLUMN_THUMB, NULL, -1);
			valid = gtk_tree_model_iter_next(store, &iter);
			}
		return;
		}

	while (!mfd && valid)
		{
		GdkPixbuf *pixbuf;

		length++;
		gtk_tree_model_get(store, &iter, SEARCH_COLUMN_POINTER, &mfd, SEARCH_COLUMN_THUMB, &pixbuf, -1);
		if (pixbuf || mfd->fd->thumb_pixbuf)
			{
			if (!pixbuf) gtk_list_store_set(GTK_LIST_STORE(store), &iter, SEARCH_COLUMN_THUMB, mfd->fd->thumb_pixbuf, -1);
			row++;
			mfd = NULL;
			}
		valid = gtk_tree_model_iter_next(store, &iter);
		}
	if (valid)
		{
		while (gtk_tree_model_iter_next(store, &iter)) length++;
		}

	if (!mfd)
		{
		sd->thumb_fd = NULL;
		thumb_loader_free(sd->thumb_loader);
		sd->thumb_loader = NULL;

		search_progress_update(sd, TRUE, -1.0);
		return;
		}

	search_progress_update(sd, FALSE, (gdouble)row/length);

	sd->thumb_fd = mfd->fd;
	thumb_loader_free(sd->thumb_loader);
	sd->thumb_loader = thumb_loader_new(options->thumbnails.max_width, options->thumbnails.max_height);

	thumb_loader_set_callbacks(sd->thumb_loader,
				   search_result_thumb_done_cb,
				   search_result_thumb_done_cb,
				   NULL,
				   sd);
	if (!thumb_loader_start(sd->thumb_loader, mfd->fd))
		{
		search_result_thumb_do(sd);
		search_result_thumb_step(sd);
		}
}

pl3_file_browser_reupdate(void)
{

	if (pl3_fb_vbox)
	{
		GtkTreeIter iter;

		GtkTreeModel *model = GTK_TREE_MODEL(pl3_fb_dir_store);

		if (mpd_stats_get_total_songs(connection) == 0 && !mpd_status_db_is_updating(connection))
		{
			gtk_widget_show(pl3_fb_warning_box);
		} else
		{
			gtk_widget_hide(pl3_fb_warning_box);
		}

		if (gtk_tree_model_get_iter_first(model, &iter))
		{
			GtkTreeIter child;
			if (!gtk_tree_model_iter_children(model, &child, &iter))
			{
				gtk_tree_store_set(GTK_TREE_STORE(model), &iter, PL3_FB_OPEN, FALSE, -1);
				gtk_tree_store_append(pl3_fb_dir_store, &child, &iter);
			}
			pl3_file_browser_reupdate_folder(&iter);
			pl3_file_browser_view_folder(gtk_tree_view_get_selection(GTK_TREE_VIEW(pl3_fb_dir_tree)), NULL);
		}
	}
}

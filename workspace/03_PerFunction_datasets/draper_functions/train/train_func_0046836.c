crawler_check_directory_cb (TrackerCrawler *crawler,
                            GFile          *directory,
                            gpointer        user_data)
{
	TrackerFileNotifierPrivate *priv;
	GFile *root, *canonical;

	priv = TRACKER_FILE_NOTIFIER (user_data)->priv;

	canonical = tracker_file_system_peek_file (priv->file_system, directory);
	root = tracker_indexing_tree_get_root (priv->indexing_tree, directory, NULL);


	if (canonical &&
	    root == canonical &&
	    root != priv->pending_index_roots->data) {
		return FALSE;
	}

	return tracker_indexing_tree_file_is_indexable (priv->indexing_tree,
	                                                directory,
	                                                G_FILE_TYPE_DIRECTORY);
}

remove_bookmarks (GeditFileBookmarksStore *model)
{
	GtkTreeIter iter;

	while (find_with_flags (GTK_TREE_MODEL (model), &iter, NULL,
				GEDIT_FILE_BOOKMARKS_STORE_IS_BOOKMARK,
				0))
	{
		remove_node (GTK_TREE_MODEL (model), &iter);
	}
}

bar_pane_keywords_dnd_can_move(GtkTreeModel *keyword_tree, GtkTreeIter *src_kw_iter, GtkTreeIter *dest_kw_iter)
{
	gchar *src_name;
	GtkTreeIter parent;

	if (dest_kw_iter && keyword_same_parent(keyword_tree, src_kw_iter, dest_kw_iter))
		{
		return TRUE;
		}
	if (!dest_kw_iter && !gtk_tree_model_iter_parent(keyword_tree, &parent, src_kw_iter))
		{
		return TRUE;
		}

	src_name = keyword_get_name(keyword_tree, src_kw_iter);
	if (keyword_exists(keyword_tree, NULL, dest_kw_iter, src_name, FALSE, NULL))
		{
		g_free(src_name);
		return FALSE;
	}
	g_free(src_name);
	return TRUE;
}

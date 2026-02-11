cb_reordered_find (GtkTreeModel *model, GtkTreePath *path, GtkTreeIter *iter,
		   GraphGuruState *s)
{
	GogObject *obj;
	gtk_tree_model_get (model, iter, PLOT_ATTR_OBJECT, &obj, -1);
	if (obj == s->search_target) {
		gtk_tree_store_move_after (s->prop_model, &s->prop_iter, iter);
		return TRUE;
	}

	return FALSE;
}

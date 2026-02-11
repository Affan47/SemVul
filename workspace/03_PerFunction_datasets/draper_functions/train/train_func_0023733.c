tracker_view_store_row_changed (TrackerView* self, GtkTreeModel* model, GtkTreePath* path, GtkTreeIter* iter) {
	gint n_children = 0;
	GtkTreeModel* _tmp0_ = NULL;
	GtkTreeIter _tmp1_ = {0};
	gint _tmp2_ = 0;
	gint _tmp3_ = 0;
	g_return_if_fail (self != NULL);
	g_return_if_fail (model != NULL);
	g_return_if_fail (path != NULL);
	g_return_if_fail (iter != NULL);
	_tmp0_ = model;
	_tmp1_ = *iter;
	_tmp2_ = gtk_tree_model_iter_n_children (_tmp0_, &_tmp1_);
	n_children = _tmp2_;
	_tmp3_ = n_children;
	if (_tmp3_ > 0) {
		GtkWidget* _tmp4_ = NULL;
		GtkTreePath* _tmp5_ = NULL;
		_tmp4_ = self->priv->view;
		_tmp5_ = path;
		gtk_tree_view_expand_row (G_TYPE_CHECK_INSTANCE_CAST (_tmp4_, GTK_TYPE_TREE_VIEW, GtkTreeView), _tmp5_, FALSE);
	}
}

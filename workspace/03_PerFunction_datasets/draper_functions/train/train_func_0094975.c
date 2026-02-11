__lambda6_ (ClocksIconView* self, GtkTreeModel* model, GtkTreePath* path, GtkTreeIter* iter) {
	gboolean result = FALSE;
	ClocksContentItem* item = NULL;
	GtkTreeModel* _tmp0_ = NULL;
	GtkTreeIter _tmp1_ = {0};
	ClocksContentItem* _tmp2_ = NULL;
	gboolean _tmp3_ = FALSE;
	gboolean _tmp4_ = FALSE;
	g_return_val_if_fail (model != NULL, FALSE);
	g_return_val_if_fail (path != NULL, FALSE);
	g_return_val_if_fail (iter != NULL, FALSE);
	_tmp0_ = model;
	_tmp1_ = *iter;
	gtk_tree_model_get ((GtkTreeModel*) G_TYPE_CHECK_INSTANCE_CAST (_tmp0_, GTK_TYPE_LIST_STORE, GtkListStore), &_tmp1_, CLOCKS_ICON_VIEW_COLUMN_ITEM, &item, -1);
	_tmp2_ = item;
	_tmp3_ = clocks_content_item_get_selectable (_tmp2_);
	_tmp4_ = _tmp3_;
	if (_tmp4_) {
		GtkTreeModel* _tmp5_ = NULL;
		GtkTreeIter _tmp6_ = {0};
		_tmp5_ = model;
		_tmp6_ = *iter;
		gtk_list_store_set (G_TYPE_CHECK_INSTANCE_CAST (_tmp5_, GTK_TYPE_LIST_STORE, GtkListStore), &_tmp6_, CLOCKS_ICON_VIEW_COLUMN_SELECTED, TRUE, -1);
	}
	result = FALSE;
	_g_object_unref0 (item);
	return result;
}

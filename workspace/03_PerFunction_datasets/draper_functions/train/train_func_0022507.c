clocks_icon_view_get_selected_items (ClocksIconView* self) {
	GList* result = NULL;
	Block7Data* _data7_;
	GtkTreeModel* _tmp0_ = NULL;
	GtkTreeModel* _tmp1_ = NULL;
	GList* _tmp2_ = NULL;
	g_return_val_if_fail (self != NULL, NULL);
	_data7_ = g_slice_new0 (Block7Data);
	_data7_->_ref_count_ = 1;
	_data7_->self = g_object_ref (self);
	_data7_->items = NULL;
	_tmp0_ = gtk_icon_view_get_model ((GtkIconView*) self);
	_tmp1_ = _tmp0_;
	gtk_tree_model_foreach (_tmp1_, ___lambda5__gtk_tree_model_foreach_func, _data7_);
	_data7_->items = g_list_reverse (_data7_->items);
	_tmp2_ = _data7_->items;
	_data7_->items = NULL;
	result = _tmp2_;
	block7_data_unref (_data7_);
	_data7_ = NULL;
	return result;
}

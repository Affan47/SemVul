build_tool_dialog_add_icon (BuildToolDialog* self, const gchar* stock_id, const gchar* label) {
	GtkTreeIter iter = {0};
	GtkListStore* _tmp0_ = NULL;
	GtkTreeIter _tmp1_ = {0};
	GtkListStore* _tmp2_ = NULL;
	GtkTreeIter _tmp3_ = {0};
	const gchar* _tmp4_ = NULL;
	const gchar* _tmp5_ = NULL;
	g_return_if_fail (self != NULL);
	g_return_if_fail (stock_id != NULL);
	g_return_if_fail (label != NULL);
	_tmp0_ = self->priv->_icons_store;
	gtk_list_store_append (_tmp0_, &_tmp1_);
	iter = _tmp1_;
	_tmp2_ = self->priv->_icons_store;
	_tmp3_ = iter;
	_tmp4_ = stock_id;
	_tmp5_ = label;
	gtk_list_store_set (_tmp2_, &_tmp3_, BUILD_TOOL_DIALOG_ICON_COLUMN_STOCK_ID, _tmp4_, BUILD_TOOL_DIALOG_ICON_COLUMN_LABEL, _tmp5_, -1);
}

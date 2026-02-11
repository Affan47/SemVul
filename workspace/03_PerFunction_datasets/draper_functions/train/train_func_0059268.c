symbols_add_most_used_category (Symbols* self) {
	GtkTreeModel* model = NULL;
	MostUsedSymbols* _tmp0_ = NULL;
	MostUsedSymbols* _tmp1_ = NULL;
	GtkTreeModel* _tmp2_ = NULL;
	GtkTreeModel* _tmp3_ = NULL;
	GtkTreeIter iter = {0};
	GtkListStore* _tmp4_ = NULL;
	GtkTreeIter _tmp5_ = {0};
	GtkListStore* _tmp6_ = NULL;
	GtkTreeIter _tmp7_ = {0};
	const gchar* _tmp8_ = NULL;
	g_return_if_fail (self != NULL);
	_tmp0_ = most_used_symbols_get_default ();
	_tmp1_ = _tmp0_;
	_tmp2_ = most_used_symbols_get_model (_tmp1_);
	_tmp3_ = _tmp2_;
	_g_object_unref0 (_tmp1_);
	model = _tmp3_;
	_tmp4_ = self->priv->_categories_store;
	gtk_list_store_append (_tmp4_, &_tmp5_);
	iter = _tmp5_;
	_tmp6_ = self->priv->_categories_store;
	_tmp7_ = iter;
	_tmp8_ = _ ("Most Used");
	gtk_list_store_set (_tmp6_, &_tmp7_, SYMBOLS_CATEGORY_COLUMN_TYPE, SYMBOLS_CATEGORY_TYPE_MOST_USED, SYMBOLS_CATEGORY_COLUMN_ICON, GTK_STOCK_ABOUT, SYMBOLS_CATEGORY_COLUMN_NAME, _tmp8_, SYMBOLS_CATEGORY_COLUMN_SYMBOLS_STORE, model, -1);
	_g_object_unref0 (model);
}

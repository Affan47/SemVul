alm_privacy_widget_remove_app_from_view (AlmPrivacyWidget* self, const gchar* app) {
	GtkTreeModel* model = NULL;
	GtkTreeView* _tmp0_ = NULL;
	GtkTreeModel* _tmp1_ = NULL;
	GtkTreeModel* _tmp2_ = NULL;
	GtkTreeIter iter = {0};
	GtkTreeModel* _tmp3_ = NULL;
	GtkTreeIter _tmp4_ = {0};
	g_return_if_fail (self != NULL);
	g_return_if_fail (app != NULL);
	_tmp0_ = self->priv->exception_list;
	_tmp1_ = gtk_tree_view_get_model (_tmp0_);
	_tmp2_ = _g_object_ref0 (_tmp1_);
	model = _tmp2_;
	_tmp3_ = model;
	gtk_tree_model_get_iter_first (_tmp3_, &_tmp4_);
	iter = _tmp4_;
	while (TRUE) {
		GValue can_app_value = {0};
		GtkTreeModel* _tmp5_ = NULL;
		GtkTreeIter _tmp6_ = {0};
		GValue _tmp7_ = {0};
		gchar* can_app = NULL;
		const gchar* _tmp8_ = NULL;
		gchar* _tmp9_ = NULL;
		const gchar* _tmp10_ = NULL;
		const gchar* _tmp11_ = NULL;
		gboolean more_entires = FALSE;
		GtkTreeModel* _tmp14_ = NULL;
		gboolean _tmp15_ = FALSE;
		gboolean _tmp16_ = FALSE;
		_tmp5_ = model;
		_tmp6_ = iter;
		gtk_tree_model_get_value (_tmp5_, &_tmp6_, 2, &_tmp7_);
		G_IS_VALUE (&can_app_value) ? (g_value_unset (&can_app_value), NULL) : NULL;
		can_app_value = _tmp7_;
		_tmp8_ = g_value_get_string (&can_app_value);
		_tmp9_ = g_strdup (_tmp8_);
		can_app = _tmp9_;
		_tmp10_ = app;
		_tmp11_ = can_app;
		if (g_strcmp0 (_tmp10_, _tmp11_) == 0) {
			GtkListStore* _tmp12_ = NULL;
			GtkTreeIter _tmp13_ = {0};
			_tmp12_ = self->priv->exception_list_store;
			_tmp13_ = iter;
			gtk_list_store_remove (_tmp12_, &_tmp13_);
			_g_free0 (can_app);
			G_IS_VALUE (&can_app_value) ? (g_value_unset (&can_app_value), NULL) : NULL;
			break;
		}
		_tmp14_ = model;
		_tmp15_ = gtk_tree_model_iter_next (_tmp14_, &iter);
		more_entires = _tmp15_;
		_tmp16_ = more_entires;
		if (!_tmp16_) {
			_g_free0 (can_app);
			G_IS_VALUE (&can_app_value) ? (g_value_unset (&can_app_value), NULL) : NULL;
			break;
		}
		_g_free0 (can_app);
		G_IS_VALUE (&can_app_value) ? (g_value_unset (&can_app_value), NULL) : NULL;
	}
	_g_object_unref0 (model);
}

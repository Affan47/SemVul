gmpc_browsers_nowplaying_select_now_playing_browser (GmpcBrowsersNowplaying* self) {
	GtkTreeView* _tmp0_ = NULL;
	GtkTreeView* tree;
	GtkTreeView* _tmp1_;
	GtkTreeSelection* _tmp2_ = NULL;
	GtkTreeSelection* _tmp3_;
	GtkTreeSelection* sel;
	const GtkTreeRowReference* _tmp4_;
	GtkTreePath* _tmp5_ = NULL;
	GtkTreePath* path;
	GtkTreePath* _tmp6_;
	g_return_if_fail (self != NULL);
	_tmp0_ = playlist3_get_category_tree_view ();
	tree = _tmp0_;
	_tmp1_ = tree;
	_tmp2_ = gtk_tree_view_get_selection (_tmp1_);
	_tmp3_ = _g_object_ref0 (_tmp2_);
	sel = _tmp3_;
	_tmp4_ = self->priv->np_ref;
	_tmp5_ = gtk_tree_row_reference_get_path (_tmp4_);
	path = _tmp5_;
	_tmp6_ = path;
	if (_tmp6_ != NULL) {
		GtkTreeSelection* _tmp7_;
		GtkTreePath* _tmp8_;
		_tmp7_ = sel;
		_tmp8_ = path;
		gtk_tree_selection_select_path (_tmp7_, _tmp8_);
	}
	_gtk_tree_path_free0 (path);
	_g_object_unref0 (sel);
}

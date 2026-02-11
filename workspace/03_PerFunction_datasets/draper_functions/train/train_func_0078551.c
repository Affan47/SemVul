latex_menu_get_indentation (LatexMenu* self) {
	gchar* result = NULL;
	MainWindow* _tmp0_ = NULL;
	DocumentView* _tmp1_ = NULL;
	DocumentView* _tmp2_ = NULL;
	gchar* _tmp3_ = NULL;
	g_return_val_if_fail (self != NULL, NULL);
	_tmp0_ = self->priv->main_window;
	_tmp1_ = main_window_get_active_view (_tmp0_);
	_tmp2_ = _tmp1_;
	_tmp3_ = document_view_get_indentation_style (_tmp2_);
	result = _tmp3_;
	return result;
}

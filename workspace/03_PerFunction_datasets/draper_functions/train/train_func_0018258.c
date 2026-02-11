utils_get_toplevel_window (GtkWidget* widget) {
	GtkWindow* result = NULL;
	GtkWidget* toplevel = NULL;
	GtkWidget* _tmp0_ = NULL;
	GtkWidget* _tmp1_ = NULL;
	GtkWidget* _tmp2_ = NULL;
	g_return_val_if_fail (widget != NULL, NULL);
	_tmp0_ = widget;
	_tmp1_ = gtk_widget_get_toplevel (_tmp0_);
	toplevel = _tmp1_;
	_tmp2_ = toplevel;
	if (G_TYPE_CHECK_INSTANCE_TYPE (_tmp2_, GTK_TYPE_WINDOW)) {
		GtkWidget* _tmp3_ = NULL;
		_tmp3_ = toplevel;
		result = G_TYPE_CHECK_INSTANCE_TYPE (_tmp3_, GTK_TYPE_WINDOW) ? ((GtkWindow*) _tmp3_) : NULL;
		return result;
	}
	result = NULL;
	return result;
}

tracker_view_view_button_press_event (TrackerView* self, GtkWidget* widget, GdkEventButton* event) {
	gboolean result = FALSE;
	GdkEventButton _tmp0_ = {0};
	guint _tmp1_ = 0U;
	g_return_val_if_fail (self != NULL, FALSE);
	g_return_val_if_fail (widget != NULL, FALSE);
	g_return_val_if_fail (event != NULL, FALSE);
	_tmp0_ = *event;
	_tmp1_ = _tmp0_.button;
	if (_tmp1_ == ((guint) 3)) {
		GtkTreePath* _tmp2_ = NULL;
		GtkTreePath* _tmp3_ = NULL;
		gboolean _tmp4_ = FALSE;
		_tmp2_ = tracker_view_get_selected_path (self);
		_tmp3_ = _tmp2_;
		_tmp4_ = _tmp3_ != NULL;
		_gtk_tree_path_free0 (_tmp3_);
		if (_tmp4_) {
			GtkMenu* _tmp5_ = NULL;
			GdkEventButton _tmp6_ = {0};
			guint _tmp7_ = 0U;
			GdkEventButton _tmp8_ = {0};
			guint32 _tmp9_ = 0U;
			_tmp5_ = self->priv->context_menu;
			_tmp6_ = *event;
			_tmp7_ = _tmp6_.button;
			_tmp8_ = *event;
			_tmp9_ = _tmp8_.time;
			gtk_menu_popup (_tmp5_, NULL, NULL, NULL, NULL, _tmp7_, _tmp9_);
		}
	}
	result = FALSE;
	return result;
}

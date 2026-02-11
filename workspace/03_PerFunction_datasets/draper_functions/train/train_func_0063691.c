clocks_header_bar_set_mode (ClocksHeaderBar* self, ClocksHeaderBarMode value) {
	ClocksHeaderBarMode _tmp0_ = 0;
	ClocksHeaderBarMode _tmp1_ = 0;
	g_return_if_fail (self != NULL);
	_tmp0_ = self->priv->_mode;
	_tmp1_ = value;
	if (_tmp0_ != _tmp1_) {
		ClocksHeaderBarMode _tmp2_ = 0;
		ClocksHeaderBarMode _tmp3_ = 0;
		_tmp2_ = value;
		self->priv->_mode = _tmp2_;
		_tmp3_ = self->priv->_mode;
		if (_tmp3_ == CLOCKS_HEADER_BAR_MODE_SELECTION) {
			GtkStyleContext* _tmp4_ = NULL;
			_tmp4_ = gtk_widget_get_style_context ((GtkWidget*) self);
			gtk_style_context_add_class (_tmp4_, "selection-mode");
		} else {
			GtkStyleContext* _tmp5_ = NULL;
			_tmp5_ = gtk_widget_get_style_context ((GtkWidget*) self);
			gtk_style_context_remove_class (_tmp5_, "selection-mode");
		}
		g_object_notify ((GObject*) self, "mode");
	}
}

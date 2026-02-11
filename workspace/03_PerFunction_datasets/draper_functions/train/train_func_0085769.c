math_display_real_key_press_event (GtkWidget* base, GdkEventKey* event) {
	MathDisplay * self;
	gboolean result = FALSE;
	GtkTextView* _tmp0_ = NULL;
	GdkEventKey _tmp1_ = {0};
	gboolean _tmp2_ = FALSE;
	self = (MathDisplay*) base;
	g_return_val_if_fail (event != NULL, FALSE);
	_tmp0_ = self->priv->text_view;
	_tmp1_ = *event;
	g_signal_emit_by_name ((GtkWidget*) _tmp0_, "key-press-event", &_tmp1_, &_tmp2_);
	result = _tmp2_;
	return result;
}

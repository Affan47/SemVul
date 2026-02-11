contacts_clickable_button_press_event (ContactsClickable* self, GdkEventButton* event) {
	gboolean result = FALSE;
	GdkEventButton _tmp0_ = {0};
	guint _tmp1_ = 0U;
	g_return_val_if_fail (self != NULL, FALSE);
	g_return_val_if_fail (event != NULL, FALSE);
	_tmp0_ = *event;
	_tmp1_ = _tmp0_.button;
	if (_tmp1_ == ((guint) 1)) {
		gboolean _tmp2_ = FALSE;
		gboolean _tmp3_ = FALSE;
		gboolean _tmp7_ = FALSE;
		_tmp3_ = self->priv->focus_on_click;
		if (_tmp3_) {
			GtkWidget* _tmp4_ = NULL;
			gboolean _tmp5_ = FALSE;
			gboolean _tmp6_ = FALSE;
			_tmp4_ = self->priv->widget;
			g_object_get (_tmp4_, "has-focus", &_tmp5_, NULL);
			_tmp6_ = _tmp5_;
			_tmp2_ = !_tmp6_;
		} else {
			_tmp2_ = FALSE;
		}
		_tmp7_ = _tmp2_;
		if (_tmp7_) {
			GtkWidget* _tmp8_ = NULL;
			_tmp8_ = self->priv->widget;
			gtk_widget_grab_focus (_tmp8_);
		}
		contacts_clickable_pressed (self);
		result = TRUE;
		return result;
	}
	result = FALSE;
	return result;
}

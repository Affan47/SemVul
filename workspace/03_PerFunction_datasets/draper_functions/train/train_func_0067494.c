gmpc_easy_command_key_press_event (GmpcEasyCommand* self, GtkWidget* widget, GdkEventKey* event) {
	gboolean result = FALSE;
	GdkEventKey _tmp0_;
	guint _tmp1_;
	GdkEventKey _tmp2_;
	guint _tmp3_;
	g_return_val_if_fail (self != NULL, FALSE);
	g_return_val_if_fail (widget != NULL, FALSE);
	g_return_val_if_fail (event != NULL, FALSE);
	_tmp0_ = *event;
	_tmp1_ = _tmp0_.keyval;
	if (_tmp1_ == ((guint) 0xff1b)) {
		gmpc_easy_command_popup_destroy (self);
		result = TRUE;
		return result;
	}
	_tmp2_ = *event;
	_tmp3_ = _tmp2_.keyval;
	if (_tmp3_ == ((guint) 0xff09)) {
		GtkWidget* _tmp4_;
		_tmp4_ = widget;
		gtk_editable_set_position (GTK_EDITABLE (_tmp4_), -1);
		result = TRUE;
		return result;
	}
	result = FALSE;
	return result;
}

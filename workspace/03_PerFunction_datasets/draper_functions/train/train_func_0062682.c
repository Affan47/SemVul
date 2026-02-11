handle_real_button_release_event (GtkWidget* base, GdkEventButton* event) {
	Handle * self;
	gboolean result = FALSE;
	GdkEventButton _tmp0_ = {0};
	guint _tmp1_ = 0U;
	GdkWindow* _tmp2_ = NULL;
	GdkCursor* _tmp3_ = NULL;
	GdkCursor* _tmp4_ = NULL;
	self = (Handle*) base;
	g_return_val_if_fail (event != NULL, FALSE);
	_tmp0_ = *event;
	_tmp1_ = _tmp0_.button;
	if (_tmp1_ != ((guint) 1)) {
		result = FALSE;
		return result;
	}
	self->priv->m_move_begined = FALSE;
	self->priv->m_press_pos.x = 0;
	self->priv->m_press_pos.y = 0;
	_tmp2_ = gtk_widget_get_window ((GtkWidget*) self);
	_tmp3_ = gdk_cursor_new (GDK_LEFT_PTR);
	_tmp4_ = _tmp3_;
	gdk_window_set_cursor (_tmp2_, _tmp4_);
	_g_object_unref0 (_tmp4_);
	g_signal_emit_by_name (self, "move-end");
	result = TRUE;
	return result;
}

_____lambda14_ (Block5Data* _data5_, GdkEventCrossing* e) {
	Switcher * self;
	gboolean result = FALSE;
	SwitcherIBusEngineButton* _tmp0_ = NULL;
	gint _tmp1_ = 0;
	self = _data5_->self;
	g_return_val_if_fail (e != NULL, FALSE);
	_tmp0_ = _data5_->button;
	gtk_widget_grab_focus ((GtkWidget*) _tmp0_);
	_tmp1_ = _data5_->index;
	self->priv->m_selected_engine = (guint) _tmp1_;
	result = TRUE;
	return result;
}

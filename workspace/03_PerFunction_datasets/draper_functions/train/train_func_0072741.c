abraca_tool_bar_on_coverart_tooltip (AbracaToolBar* self, GtkWidget* widget, gint xpos, gint ypos, gboolean mode, GtkTooltip* tooltip) {
	gboolean result = FALSE;
	GdkPixbuf* _tmp0_;
	g_return_val_if_fail (self != NULL, FALSE);
	g_return_val_if_fail (widget != NULL, FALSE);
	g_return_val_if_fail (tooltip != NULL, FALSE);
	_tmp0_ = self->priv->_coverart_big;
	if (_tmp0_ != NULL) {
		GtkTooltip* _tmp1_;
		GdkPixbuf* _tmp2_;
		_tmp1_ = tooltip;
		_tmp2_ = self->priv->_coverart_big;
		gtk_tooltip_set_icon (_tmp1_, _tmp2_);
		result = TRUE;
		return result;
	}
	result = FALSE;
	return result;
}

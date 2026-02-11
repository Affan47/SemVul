_gmpc_browsers_nowplaying___lambda94_ (GmpcBrowsersNowplaying* self, MpdObj* source, gint connect) {
	gboolean _tmp0_ = FALSE;
	gint _tmp1_;
	gboolean _tmp3_;
	g_return_if_fail (source != NULL);
	_tmp1_ = connect;
	if (_tmp1_ == 0) {
		GtkScrolledWindow* _tmp2_;
		_tmp2_ = self->priv->paned;
		_tmp0_ = _tmp2_ != NULL;
	} else {
		_tmp0_ = FALSE;
	}
	_tmp3_ = _tmp0_;
	if (_tmp3_) {
		gmpc_browsers_nowplaying_update_not_playing (self);
	}
}

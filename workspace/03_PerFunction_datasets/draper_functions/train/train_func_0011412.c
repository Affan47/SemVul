chess_engine_uci_construct (GType object_type, gchar** options, int options_length1) {
	ChessEngineUCI * self = NULL;
	gchar** _tmp0_;
	gint _tmp0__length1;
	gchar** _tmp1_;
	gint _tmp1__length1;
	gchar* _tmp2_ = NULL;
	gchar* _tmp3_;
	self = (ChessEngineUCI*) chess_engine_construct (object_type);
	_tmp0_ = options;
	_tmp0__length1 = options_length1;
	_tmp1_ = (_tmp0_ != NULL) ? _vala_array_dup7 (_tmp0_, _tmp0__length1) : ((gpointer) _tmp0_);
	_tmp1__length1 = _tmp0__length1;
	self->priv->options = (_vala_array_free (self->priv->options, self->priv->options_length1, (GDestroyNotify) g_free), NULL);
	self->priv->options = _tmp1_;
	self->priv->options_length1 = _tmp1__length1;
	self->priv->_options_size_ = self->priv->options_length1;
	_tmp2_ = g_new0 (gchar, 0);
	self->priv->buffer = (g_free (self->priv->buffer), NULL);
	self->priv->buffer = _tmp2_;
	self->priv->buffer_length1 = 0;
	self->priv->_buffer_size_ = self->priv->buffer_length1;
	_tmp3_ = g_strdup ("");
	_g_free0 (self->priv->moves);
	self->priv->moves = _tmp3_;
	g_signal_connect_object ((ChessEngine*) self, "starting", (GCallback) _chess_engine_uci_start_cb_chess_engine_starting, self, 0);
	return self;
}

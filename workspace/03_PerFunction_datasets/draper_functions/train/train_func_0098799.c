__lambda28_ (Desktop* self) {
	guint _tmp0_ = 0U;
	_tmp0_ = self->priv->idle_rebuild_id;
	if (_tmp0_ == ((guint) 0)) {
		guint _tmp1_ = 0U;
		_tmp1_ = g_idle_add_full (G_PRIORITY_DEFAULT_IDLE, ____lambda29__gsource_func, g_object_ref (self), g_object_unref);
		self->priv->idle_rebuild_id = _tmp1_;
	}
}

clocks_window_finalize (GObject* obj) {
	ClocksWindow * self;
	GSettings* _tmp0_ = NULL;
	self = G_TYPE_CHECK_INSTANCE_CAST (obj, CLOCKS_TYPE_WINDOW, ClocksWindow);
	_tmp0_ = self->priv->settings;
	g_settings_apply (_tmp0_);
	_g_object_unref0 (self->priv->header_bar);
	_g_object_unref0 (self->priv->stack);
	_g_object_unref0 (self->priv->stack_switcher);
	_g_object_unref0 (self->priv->settings);
	self->priv->panels = (_vala_array_free (self->priv->panels, self->priv->panels_length1, (GDestroyNotify) g_object_unref), NULL);
	G_OBJECT_CLASS (clocks_window_parent_class)->finalize (obj);
}

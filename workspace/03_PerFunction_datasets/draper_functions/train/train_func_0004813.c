dvb_player_thread_finalize (GObject* obj) {
	DVBPlayerThread * self;
	self = G_TYPE_CHECK_INSTANCE_CAST (obj, DVB_TYPE_PLAYER_THREAD, DVBPlayerThread);
	_g_object_unref0 (self->priv->_active_channels);
	_g_object_unref0 (self->priv->_device);
	g_rec_mutex_clear (&self->priv->__lock_pipeline);
	_gst_object_unref0 (self->priv->pipeline);
	g_rec_mutex_clear (&self->priv->__lock_elements_map);
	_g_object_unref0 (self->priv->elements_map);
	_g_object_unref0 (self->priv->epgscanner);
	_gst_object_unref0 (self->priv->dvbbasebin);
	g_rec_mutex_clear (&self->priv->__lock_destroyed);
	G_OBJECT_CLASS (dvb_player_thread_parent_class)->finalize (obj);
}

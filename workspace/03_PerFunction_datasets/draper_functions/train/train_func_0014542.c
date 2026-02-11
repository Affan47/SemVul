unity_playlist_finalize (GObject* obj) {
	UnityPlaylist * self;
	self = G_TYPE_CHECK_INSTANCE_CAST (obj, UNITY_TYPE_PLAYLIST, UnityPlaylist);
	_g_free0 (self->priv->_id);
	_g_free0 (self->priv->_name);
	_g_object_unref0 (self->priv->_icon);
	_g_date_time_unref0 (self->priv->_creation_date);
	_g_date_time_unref0 (self->priv->_modification_date);
	_g_date_time_unref0 (self->priv->_last_play_date);
	G_OBJECT_CLASS (unity_playlist_parent_class)->finalize (obj);
}

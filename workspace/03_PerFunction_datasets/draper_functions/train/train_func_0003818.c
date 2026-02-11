unity_music_player_construct (GType object_type, const gchar* desktop) {
	UnityMusicPlayer * self = NULL;
	const gchar* _tmp0_ = NULL;
	GPtrArray* _tmp1_ = NULL;
	g_return_val_if_fail (desktop != NULL, NULL);
	_tmp0_ = desktop;
	self = (UnityMusicPlayer*) g_object_new (object_type, "desktop-file-name", _tmp0_, NULL);
	_tmp1_ = g_ptr_array_new_with_free_func (_g_object_unref0_);
	_g_ptr_array_unref0 (self->priv->internal_playlists);
	self->priv->internal_playlists = _tmp1_;
	return self;
}

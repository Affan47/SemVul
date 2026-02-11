mpris2_controller_fetch_active_playlist (Mpris2Controller* self) {
	gboolean result = FALSE;
	gboolean _tmp0_ = FALSE;
	PlaylistsMenuitem* playlists_item = NULL;
	PlayerController* _tmp1_ = NULL;
	GeeArrayList* _tmp2_ = NULL;
	gpointer _tmp3_ = NULL;
	PlayerItem* _tmp4_ = NULL;
	PlaylistsMenuitem* _tmp5_ = NULL;
	PlaylistsMenuitem* _tmp6_ = NULL;
	MprisPlaylists* _tmp7_ = NULL;
	ActivePlaylistContainer* _tmp8_ = NULL;
	ActivePlaylistContainer* _tmp9_ = NULL;
	ActivePlaylistContainer* _tmp10_ = NULL;
	PlaylistDetails* _tmp11_ = NULL;
	PlaylistDetails _tmp12_ = {0};
	g_return_val_if_fail (self != NULL, FALSE);
	_tmp0_ = mpris2_controller_validate_playlists_details (self);
	if (_tmp0_ == FALSE) {
		result = FALSE;
		return result;
	}
	_tmp1_ = self->priv->_owner;
	_tmp2_ = _tmp1_->custom_items;
	_tmp3_ = gee_abstract_list_get ((GeeAbstractList*) _tmp2_, (gint) PLAYER_CONTROLLER_WIDGET_ORDER_PLAYLISTS);
	_tmp4_ = (PlayerItem*) _tmp3_;
	_tmp5_ = G_TYPE_CHECK_INSTANCE_TYPE (_tmp4_, TYPE_PLAYLISTS_MENUITEM) ? ((PlaylistsMenuitem*) _tmp4_) : NULL;
	if (_tmp5_ == NULL) {
		_g_object_unref0 (_tmp4_);
	}
	playlists_item = _tmp5_;
	_tmp6_ = playlists_item;
	_tmp7_ = self->priv->_playlists;
	_tmp8_ = mpris_playlists_get_ActivePlaylist (_tmp7_);
	_tmp9_ = _tmp8_;
	_tmp10_ = _tmp9_;
	_tmp11_ = (*_tmp10_).details;
	_tmp12_ = *_tmp11_;
	playlists_menuitem_active_playlist_update (_tmp6_, &_tmp12_);
	_active_playlist_container_free0 (_tmp10_);
	result = FALSE;
	_g_object_unref0 (playlists_item);
	return result;
}

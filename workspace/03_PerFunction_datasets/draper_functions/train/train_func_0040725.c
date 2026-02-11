active_playlist_container_copy (const ActivePlaylistContainer* self, ActivePlaylistContainer* dest) {
	gboolean _tmp0_ = FALSE;
	PlaylistDetails* _tmp1_ = NULL;
	PlaylistDetails* _tmp2_ = NULL;
	_tmp0_ = (*self).valid;
	(*dest).valid = _tmp0_;
	_tmp1_ = (*self).details;
	_tmp2_ = _playlist_details_dup0 (_tmp1_);
	_playlist_details_free0 ((*dest).details);
	(*dest).details = _tmp2_;
}

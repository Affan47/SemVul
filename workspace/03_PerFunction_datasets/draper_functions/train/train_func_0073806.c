active_playlist_container_destroy (ActivePlaylistContainer* self) {
	_playlist_details_free0 ((*self).details);
}

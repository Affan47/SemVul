sfx_song_set_status(sfx_state_t *self, song_handle_t handle, int status)
{
	song_t *song = song_lib_find(self->songlib, handle);
	ASSERT_SONG(song);
#ifdef DEBUG_SONG_API
	fprintf(stderr, "[sfx-core] Setting song status to %d"
		" (0:stop, 1:play, 2:susp, 3:wait): %08lx\n", status, handle);
#endif

	 _sfx_set_song_status(self, song, status);

	_update(self);
}

add_to_playlist_and_play_cb (TotemPlaylist *playlist, GAsyncResult *async_result, AddToPlaylistData *data)
{
	int end;
	gboolean playlist_changed;

	playlist_changed = totem_playlist_add_mrl_finish (playlist, async_result);

	end = totem_playlist_get_last (playlist);

	totem_signal_unblock_by_data (playlist, data->totem);

	if (playlist_changed && end != -1) {
		char *mrl, *subtitle;

		subtitle = NULL;
		totem_playlist_set_current (playlist, end);
		mrl = totem_playlist_get_current_mrl (playlist, &subtitle);
		totem_action_set_mrl_and_play (data->totem, mrl, subtitle);
		g_free (mrl);
		g_free (subtitle);
	}


	g_object_unref (data->totem);
	g_free (data->uri);
	g_free (data->display_name);
	g_slice_free (AddToPlaylistData, data);
}

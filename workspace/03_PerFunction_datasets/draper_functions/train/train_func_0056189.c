media_player_stop (MediaPlayer *player)
{
	if (player->watch_id) {
		g_source_remove (player->watch_id);

		player->watch_id = 0;
	}

	if (player->player != NULL) {
		gst_element_set_state (player->player, GST_STATE_NULL);
	}

	media_player_set_state (player, MEDIA_PLAYER_STOPPED);
}

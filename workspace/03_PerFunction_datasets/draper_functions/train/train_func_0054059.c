rb_player_gst_xfade_playing (RBPlayer *iplayer)
{
	RBPlayerGstXFade *player = RB_PLAYER_GST_XFADE (iplayer);
	gboolean playing = FALSE;
	RBXFadeStream *stream;

	if (player->priv->sink_state != SINK_PLAYING)
		return FALSE;


	g_rec_mutex_lock (&player->priv->stream_list_lock);

	stream = find_stream_by_state (player, PLAYING | FADING_IN);
	if (stream != NULL) {
		playing = TRUE;
		g_object_unref (stream);
	}
	g_rec_mutex_unlock (&player->priv->stream_list_lock);
	return playing;
}

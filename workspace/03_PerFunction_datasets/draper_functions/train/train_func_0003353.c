load_cached_top_tracks (RBAudioscrobblerUser *user)
{
	char *filename;
	char *data;

	filename = calculate_cached_response_path (user, "top_tracks");


	if (user->priv->top_tracks != NULL) {
		g_ptr_array_unref (user->priv->top_tracks);
		user->priv->top_tracks = NULL;
	}


	if (g_file_get_contents (filename, &data, NULL, NULL) == TRUE) {
		rb_debug ("loading cached top tracks");
		user->priv->top_tracks = parse_top_tracks (user, data);
	}


	g_signal_emit (user, rb_audioscrobbler_user_signals[TOP_TRACKS_UPDATED],
	               0, user->priv->top_tracks);

	g_free (filename);
	g_free (data);
}

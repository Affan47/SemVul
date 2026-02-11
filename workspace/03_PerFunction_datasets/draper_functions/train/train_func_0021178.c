media_player_bus_check_errors (MediaPlayer *player, GstMessage *message)
{


	switch (GST_MESSAGE_TYPE (message)) {
	case GST_MESSAGE_ERROR: {
		GError *err;
		gchar *debug;

		gst_message_parse_error (message, &err, &debug);

		if (player->error_handler)
			player->error_handler (player, err, player->error_handler_data);

		g_error_free (err);
		g_free (debug);

		return FALSE;
		break;
	}
	default:
		break;
	}


	return TRUE;
}

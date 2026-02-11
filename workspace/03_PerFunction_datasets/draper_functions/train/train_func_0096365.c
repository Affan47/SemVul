rb_audioscrobbler_user_data_free (RBAudioscrobblerUserData *data)
{
	if (data->image != NULL) {
		g_object_unref (data->image);
	}
	g_free (data->url);

	switch (data->type) {
	case RB_AUDIOSCROBBLER_USER_DATA_TYPE_USER_INFO:
		g_free (data->user_info.username);
		g_free (data->user_info.playcount);
		break;
	case RB_AUDIOSCROBBLER_USER_DATA_TYPE_TRACK:
		g_free (data->track.title);
		g_free (data->track.artist);
		break;
	case RB_AUDIOSCROBBLER_USER_DATA_TYPE_ARTIST:
		g_free (data->artist.name);
		break;
	}

	g_slice_free (RBAudioscrobblerUserData, data);
}

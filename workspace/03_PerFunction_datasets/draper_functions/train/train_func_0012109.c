totem_object_action_play (TotemObject *totem)
{
	GError *err = NULL;
	int retval;
	char *msg, *disp;

	if (totem->mrl == NULL)
		return;

	if (bacon_video_widget_is_playing (totem->bvw) != FALSE)
		return;

	retval = bacon_video_widget_play (totem->bvw,  &err);
	play_pause_set_label (totem, retval ? STATE_PLAYING : STATE_STOPPED);

	if (retval != FALSE) {
		if (totem->has_played_emitted == FALSE) {
			totem_file_has_played (totem, totem->mrl);
			totem->has_played_emitted = TRUE;
		}
		return;
	}

	disp = totem_uri_escape_for_display (totem->mrl);
	msg = g_strdup_printf(_("Totem could not play '%s'."), disp);
	g_free (disp);

	totem_action_error (totem, msg, err->message);
	totem_action_stop (totem);
	g_free (msg);
	g_error_free (err);
}

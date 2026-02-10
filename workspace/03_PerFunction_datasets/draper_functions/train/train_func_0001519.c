on_eos_event (GtkWidget *widget, TotemObject *totem)
{
	reset_seek_status (totem);

	if (bacon_video_widget_get_logo_mode (totem->bvw) != FALSE)
		return FALSE;

	if (totem_playlist_has_next_mrl (totem->playlist) == FALSE &&
	    totem_playlist_get_repeat (totem->playlist) == FALSE &&
	    (totem_playlist_get_last (totem->playlist) != 0 ||
	     totem_is_seekable (totem) == FALSE)) {
		char *mrl, *subtitle;


		totem_playlist_set_at_start (totem->playlist);
		update_buttons (totem);
		totem_action_stop (totem);
		mrl = totem_playlist_get_current_mrl (totem->playlist, &subtitle);
		totem_action_set_mrl_with_warning (totem, mrl, subtitle, FALSE);
		bacon_video_widget_pause (totem->bvw);
		g_free (mrl);
		g_free (subtitle);
	} else {
		if (totem_playlist_get_last (totem->playlist) == 0 &&
		    totem_is_seekable (totem)) {
			if (totem_playlist_get_repeat (totem->playlist) != FALSE) {
				totem_action_seek_time (totem, 0, FALSE);
				totem_action_play (totem);
			} else {
				totem_action_pause (totem);
				totem_action_seek_time (totem, 0, FALSE);
			}
		} else {
			totem_action_next (totem);
		}
	}

	return FALSE;
}

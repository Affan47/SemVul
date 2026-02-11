reset_seek_status (TotemObject *totem)
{


	if (totem->seek_lock != FALSE) {
		totem_statusbar_set_seeking (TOTEM_STATUSBAR (totem->statusbar), FALSE);
		totem_time_label_set_seeking (TOTEM_TIME_LABEL (totem->fs->time_label), FALSE);
		totem->seek_lock = FALSE;
		bacon_video_widget_seek (totem->bvw, 0, NULL);
		totem_action_stop (totem);
	}
}

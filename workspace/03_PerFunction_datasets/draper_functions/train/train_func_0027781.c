alarm_player_start (Alarm *alarm)
{
	AlarmPrivate *priv = ALARM_PRIVATE (alarm);

	if (priv->player == NULL) {
		priv->player = media_player_new (alarm->sound_file,
										 alarm->sound_loop,
										 alarm_player_state_cb, alarm,
										 alarm_player_error_cb, alarm);
		if (priv->player == NULL) {

			alarm_error_trigger (alarm, ALARM_ERROR_PLAY,
				_("Could not create player! Please check your sound settings."));
			return;
		}
	} else {
		media_player_set_uri (priv->player, alarm->sound_file);
	}

	media_player_start (priv->player);

	g_debug ("Alarm(%p) #%d: player_start...", alarm, alarm->id);


	priv->player_timer_id = g_timeout_add_seconds(ALARM_SOUND_TIMEOUT, alarm_player_timeout, alarm);
}

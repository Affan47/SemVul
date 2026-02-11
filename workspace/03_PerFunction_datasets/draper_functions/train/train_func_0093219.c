print_status(struct mpd_status *status)
{
	const struct mpd_audio_format *audio_format;

	LOG_INFO("volume: %i", mpd_status_get_volume(status));
	LOG_INFO("repeat: %i", mpd_status_get_repeat(status));
	LOG_INFO("single: %i", mpd_status_get_single(status));
	LOG_INFO("consume: %i", mpd_status_get_consume(status));
	LOG_INFO("random: %i", mpd_status_get_random(status));
	LOG_INFO("queue version: %u", mpd_status_get_queue_version(status));
	LOG_INFO("queue length: %i", mpd_status_get_queue_length(status));

	if (mpd_status_get_state(status) == MPD_STATE_PLAY ||
	    mpd_status_get_state(status) == MPD_STATE_PAUSE) {
		LOG_INFO("song: %i", mpd_status_get_song_pos(status));
		LOG_INFO("elaspedTime: %i", mpd_status_get_elapsed_time(status));
		LOG_INFO("elasped_ms: %u\n", mpd_status_get_elapsed_ms(status));
		LOG_INFO("totalTime: %i", mpd_status_get_total_time(status));
		LOG_INFO("bitRate: %i", mpd_status_get_kbit_rate(status));
	}

	audio_format = mpd_status_get_audio_format(status);
	if (audio_format != NULL) {
		printf("sampleRate: %i\n", audio_format->sample_rate);
		printf("bits: %i\n", audio_format->bits);
		printf("channels: %i\n", audio_format->channels);
	}
}

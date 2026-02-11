event_music_first_pattern()
{
	if ( Event_music_inited == FALSE ) {
		return;
	}

	if ( Event_music_enabled == FALSE ) {
		return;
	}

	if ( Event_music_level_inited == FALSE ) {
		event_music_level_init();
	}

	if ( Event_music_level_inited == FALSE ) {
		return;
	}

	if ( Event_music_begun == TRUE ) {
		return;
	}

	if ( Current_pattern != -1 ) {
		if (  audiostream_is_playing(Patterns[Current_pattern].handle) )
			audiostream_stop( Patterns[Current_pattern].handle );
	}

	Pattern_timer_id = 2000;

	Event_music_begun = FALSE;
	if ( Event_Music_battle_started == TRUE ) {
		Current_pattern = SONG_BTTL_1;
	}
	else {
		Current_pattern = SONG_NRML_1;
	}
}

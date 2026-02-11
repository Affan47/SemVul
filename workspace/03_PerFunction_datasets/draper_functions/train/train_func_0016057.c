event_music_level_init(int force_soundtrack)
{
	int					i;
	SOUNDTRACK_INFO	*strack;

	if (Cmdline_freespace_no_music)
		return;

	if (!audiostream_is_inited())
		return;

	if (Event_music_level_inited == TRUE)
		return;

	Current_pattern = -1;
	Current_nrml = SONG_NRML_1;

	if (Event_music_inited == FALSE)
		return;


	if (force_soundtrack != -1)
		Current_soundtrack_num = force_soundtrack;

	if (Current_soundtrack_num < 0)
	{
		return;


	}

	Assert(Current_soundtrack_num >= 0 && Current_soundtrack_num < Num_soundtracks);

	if (Current_soundtrack_num < 0 || Current_soundtrack_num > Num_soundtracks)
		return;

	strack = &Soundtracks[Current_soundtrack_num];


	for (i = 0; i < MAX_PATTERNS; i++)
	{
		if (!strnicmp(strack->pattern_fnames[i], NOX("none.wav"), 4))
		{
			Patterns[i].handle = -1;
			continue;
		}

		Patterns[i].handle = audiostream_open( strack->pattern_fnames[i], ASF_EVENTMUSIC );

		if (Patterns[i].handle >= 0)
		{
			Event_music_level_inited = TRUE;
			Event_music_enabled = TRUE;
		}

		pattern_info *pip = &Pattern_info[i];


		if (strack->flags & EMF_CYCLE_FS1)
			Patterns[i].default_next_pattern = pip->pattern_default_next_fs1;
		else
			Patterns[i].default_next_pattern = pip->pattern_default_next_fs2;

		Patterns[i].next_pattern = Patterns[i].default_next_pattern;
		Patterns[i].default_loop_for = pip->pattern_loop_for;
		Patterns[i].loop_for = Patterns[i].default_loop_for;
		Patterns[i].force_pattern = FALSE;
		Patterns[i].can_force = pip->pattern_can_force;
		Patterns[i].samples_per_measure = Pattern_samples_per_measure[Current_soundtrack_num][i];
		Patterns[i].num_measures = Pattern_num_measures[Current_soundtrack_num][i];
	}

	Num_enemy_arrivals = 0;
	Num_friendly_arrivals = 0;
	Battle_over_timestamp = timestamp(BATTLE_CHECK_INTERVAL);
	Mission_over_timestamp = timestamp(BATTLE_CHECK_INTERVAL);
	Next_arrival_timestamp = timestamp(1);
	Victory2_music_played = 0;
	Check_for_battle_music = 0;

	if (Event_music_level_inited)
	{
		if (force_soundtrack >= 0)
			event_music_first_pattern();
	}
}

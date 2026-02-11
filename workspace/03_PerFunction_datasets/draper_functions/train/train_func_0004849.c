event_music_cycle_pattern()
{

	int new_pattern = Patterns[Current_pattern].next_pattern;


	if (!(Soundtracks[Current_soundtrack_num].flags & EMF_CYCLE_FS1))
	{
		if (Current_pattern == SONG_BTTL_3 && new_pattern == SONG_BTTL_1)
		{

			if (Player_obj != NULL && Player_ship != NULL)
			{
				Assert(Player_ship->ship_max_hull_strength != 0.0f);

				float integrity = Player_obj->hull_strength / Player_ship->ship_max_hull_strength;
				if (integrity < HULL_VALUE_TO_PLAY_INTENSE_BATTLE_MUSIC)
					new_pattern = SONG_BTTL_2;
			}
		}
	}


	if ((new_pattern == SONG_BTTL_2) && (Patterns[SONG_BTTL_2].handle < 0))
	{
		new_pattern = SONG_BTTL_1;
	}
	else if ((new_pattern == SONG_BTTL_3) && (Patterns[SONG_BTTL_3].handle < 0))
	{
		if ((Current_pattern == SONG_BTTL_2) || (Patterns[SONG_BTTL_2].handle < 0))
			new_pattern = SONG_BTTL_1;
		else
			new_pattern = SONG_BTTL_2;
	}


	if ((new_pattern == SONG_NRML_2) && (Patterns[SONG_NRML_2].handle < 0))
	{
		new_pattern = SONG_NRML_1;
	}
	else if ((new_pattern == SONG_NRML_3) && (Patterns[SONG_NRML_3].handle < 0))
	{
		new_pattern = SONG_NRML_1;
	}

	return new_pattern;
}

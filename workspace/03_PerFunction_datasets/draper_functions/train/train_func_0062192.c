barracks_delete_pilot()
{
	char buf[MAX_FILENAME_LEN];
	int active = 0;
	int del_rval;

	if (!Num_pilots) {
		gamesnd_play_iface(SND_GENERAL_FAIL);
		return;
	}

	if (Player_sel_mode == PLAYER_SELECT_MODE_MULTI) {
		gamesnd_play_iface(SND_GENERAL_FAIL);
		popup(PF_TITLE_BIG | PF_TITLE_RED | PF_USE_AFFIRMATIVE_ICON, 1, POPUP_OK, XSTR("Disabled!\n\nMulti and single player pilots are now identical. "
					"Deleting a multi-player pilot will also delete all single-player data for that pilot.\n\nAs a safety precaution, pilots can only be "
					"deleted from the single-player menu.", 1598));
		return;
	}

	int popup_rval = popup(PF_TITLE_BIG | PF_TITLE_RED, 2, POPUP_NO, POPUP_YES, XSTR( "Warning!\n\nAre you sure you wish to delete this pilot?", 65));
	if (popup_rval != 1) {
		return;
	}

	if (!stricmp(Pilots[Selected_line], Cur_pilot->callsign)) {
		active = 1;
	}

	strcpy_s(buf, Pilots[Selected_line]);

	del_rval = delete_pilot_file(buf);

	if ( !del_rval ) {
		popup(PF_USE_AFFIRMATIVE_ICON | PF_TITLE_BIG | PF_TITLE_RED, 1, POPUP_OK, XSTR("Error\nFailed to delete pilot file. File may be read-only.", 1599));
		return;
	} else {
		if (active) {
			Cur_pilot->callsign[0] = 0;
		}
	}

	for (int i=Selected_line; i<Num_pilots-1; i++) {
		strcpy(Pilots[i], Pilots[i + 1]);
		Pilot_ranks[i] = Pilot_ranks[i + 1];
	}

	Num_pilots--;
	if (Selected_line >= Num_pilots) {
		Selected_line = Num_pilots - 1;
	}

	if (active) {
		if (Selected_line >= 0) {
			barracks_new_pilot_selected();
		} else {
			Cur_pilot->callsign[0] = 0;
		}
	}

	gamesnd_play_iface(SND_USER_SELECT);
}

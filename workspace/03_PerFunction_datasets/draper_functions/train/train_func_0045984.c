barracks_create_new_pilot()
{

	if (Num_pilots >= MAX_PILOTS) {
		gamesnd_play_iface(SND_GENERAL_FAIL);
		return;
	}


	gamesnd_play_iface(SND_SCROLL);


	if (strlen(Player->callsign)) {
		Pilot.save_player(Player);
	}


	int idx = Num_pilots;
	Assert(Num_pilots >= 0);
	while (idx--) {
		strcpy(Pilots[idx + 1], Pilots[idx]);
		Pilot_ranks[idx + 1] = Pilot_ranks[idx];
	}

	Selected_line = 0;
	Num_pilots++;
	Pilots[Selected_line][0] = 0;
	Pilot_ranks[Selected_line] = 0;
	List_scroll_offset = 0;


	barracks_set_callsign_enter_mode(true);

	Inputbox.set_focus();

	Inputbox.set_text("");

	Inputbox.update_dimensions(Barracks_list_coords[gr_screen.res][BARRACKS_X_COORD], Barracks_list_coords[gr_screen.res][BARRACKS_Y_COORD], Barracks_list_coords[gr_screen.res][BARRACKS_W_COORD], gr_get_font_height());
}

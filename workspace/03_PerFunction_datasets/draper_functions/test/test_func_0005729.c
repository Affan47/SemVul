ss_return_name(int wing_block, int wing_slot, char *name)
{
	ss_slot_info	*ws;
	wing				*wp;

	Assert( Ss_wings != NULL );

	ws = &Ss_wings[wing_block].ss_slots[wing_slot];
	wp = &Wings[Ss_wings[wing_block].wingnum];

	if (!Wss_num_wings) {
		strcpy(name, Player->callsign);
		return;
	}


	if ( ws->sa_index != -1 ) {
		strcpy(name, Parse_objects[ws->sa_index].name);
	} else {
		ship *sp;
		sp = &Ships[wp->ship_index[wing_slot]];


		if(Game_mode & GM_MULTIPLAYER){
			int player_index = multi_find_player_by_object(&Objects[sp->objnum]);
			if(player_index != -1){
				strcpy(name,Net_players[player_index].m_player->callsign);
			} else {
				strcpy(name,sp->ship_name);
			}
		} else {
			strcpy(name, sp->ship_name);
		}
	}
}

debrief_close()
{
	int i;

	Assert(Debrief_inited);


	if (Game_mode & GM_MULTIPLAYER) {

		if (multi_debrief_stats_accept_code() != 1) {
			if(MULTIPLAYER_MASTER){
				for(i=0; i<MAX_PLAYERS; i++){
					if(MULTI_CONNECTED(Net_players[i]) && !MULTI_STANDALONE(Net_players[i]) && !MULTI_PERM_OBSERVER(Net_players[i]) && (Net_players[i].m_player != NULL)){
						scoring_backout_accept(&Net_players[i].m_player->stats);
					}
				}
			} else {
				scoring_backout_accept( &Player->stats );
			}
		}
	} else {

		if( !Debrief_accepted || !(Game_mode & GM_CAMPAIGN_MODE) ){

			if ( Game_mode & GM_CAMPAIGN_MODE ) {
				Campaign.next_mission = Campaign.current_mission;
			}
			scoring_backout_accept( &Player->stats );
		}
	}


	if (Debrief_accepted) {
		Player->show_skip_popup = 1;
	}

	if (Num_debrief_lines) {
		for (i=0; i<Num_debrief_lines; i++){
			if (Text[i]){
				vm_free(Text[i]);
			}
		}
	}


	mission_debrief_common_reset();


	Debrief_award_text_num_lines = 0;

	debrief_voice_unload_all();
	common_music_close();
	chatbox_close();


	if (Background_bitmap >= 0){
		bm_release(Background_bitmap);
	}

	if (Award_bg_bitmap >= 0){
		bm_release(Award_bg_bitmap);
	}

	if (Rank_bitmap >= 0){
		bm_release(Rank_bitmap);
	}

	if (Medal_bitmap >= 0){
		bm_release(Medal_bitmap);
	}

	if (Badge_bitmap >= 0){
		bm_release(Badge_bitmap);
	}

	if (Wings_bitmap >= 0) {
		bm_release(Wings_bitmap);
	}

	if (Crest_bitmap >= 0) {
		bm_release(Crest_bitmap);
	}

	Debrief_ui_window.destroy();
	common_free_interface_palette();
	show_stats_close();

	if (Game_mode & GM_MULTIPLAYER){
		multi_debrief_close();
	}

	if(Debrief_stats_kills != NULL)
	{
		delete[] Debrief_stats_kills;
		Debrief_stats_kills = NULL;
	}
	game_flush();

	Stage_voice = -1;

	Debriefing_paused = 0;

	Debrief_inited = 0;
}

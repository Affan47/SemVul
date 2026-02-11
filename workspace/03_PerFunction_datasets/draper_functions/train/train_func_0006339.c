debrief_set_multi_clients( int stage_count, int active_stages[] )
{
	int i;


	if(MULTI_TEAM){
		Debriefing = &Debriefings[Net_player->p_info.team];
	} else {
		Debriefing = &Debriefings[0];
	}


	Num_debrief_stages = 0;


	for (i = 0; i < stage_count; i++) {
		Debrief_stages[Num_debrief_stages++] = &Debriefing->stages[active_stages[i]];
	}

	Debrief_multi_stages_loaded = 1;
}

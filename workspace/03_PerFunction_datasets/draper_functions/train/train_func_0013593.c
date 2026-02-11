brief_do_start_pressed()
{
	if ( Current_brief_stage != 0 ) {
		gamesnd_play_iface(SND_BRIEF_STAGE_CHG);
		Current_brief_stage = 0;
		if ( Quick_transition_stage != -1 )
			brief_transition_reset();
	} else {
		gamesnd_play_iface(SND_GENERAL_FAIL);
	}
	Assert(Current_brief_stage >= 0);
}

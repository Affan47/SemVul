debrief_init_music()
{
	int score = SCORE_DEBRIEF_AVERAGE;

	Debrief_music_timeout = 0;

	if ( (Game_mode & GM_CAMPAIGN_MODE) && (Campaign.next_mission == Campaign.current_mission) ) {

		score = SCORE_DEBRIEF_FAIL;
	} else if ( mission_goals_met() ) {

		score = SCORE_DEBRIEF_SUCCESS;
	} else {

		score = SCORE_DEBRIEF_AVERAGE;
	}


	if ( MULTIPLAYER_CLIENT && (score == SCORE_DEBRIEF_AVERAGE) ) {
		Debrief_music_timeout = timestamp(2000);
		return;
	}

	common_music_init(score);
}

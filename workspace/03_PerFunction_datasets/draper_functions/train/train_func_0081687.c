scoring_do_accept(scoring_struct *score)
{
	int idx;


	if ( score->m_medal_earned != -1 ){
		score->medals[score->m_medal_earned]++;
	}


	if (The_mission.game_type == MISSION_TYPE_TRAINING){
		return;
	}

	scoring_eval_rank(score);
	scoring_eval_badges(score);

	score->kill_count += score->m_kill_count;
	score->kill_count_ok += score->m_kill_count_ok;

	score->score += score->m_score;
	score->assists += score->m_assists;
	score->p_shots_fired += score->mp_shots_fired;
	score->s_shots_fired += score->ms_shots_fired;

	score->p_shots_hit += score->mp_shots_hit;
	score->s_shots_hit += score->ms_shots_hit;

	score->p_bonehead_hits += score->mp_bonehead_hits;
	score->s_bonehead_hits += score->ms_bonehead_hits;
	score->bonehead_kills += score->m_bonehead_kills;

	for(idx=0;idx<MAX_SHIP_CLASSES;idx++){
		score->kills[idx] = (int)(score->kills[idx] + score->m_okKills[idx]);
	}


	score->flight_time += (unsigned int)f2fl(Missiontime);
	score->last_backup = score->last_flown;
	score->last_flown = (_fs_time_t)time(NULL);
	score->missions_flown++;
}

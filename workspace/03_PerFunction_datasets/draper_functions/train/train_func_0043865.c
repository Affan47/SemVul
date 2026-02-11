highscore(int prof)
{
	if(-1 == prof)
		return profiles[currentProfile].last_scene;
	else if(-2 == prof)
		return high_tbl[0].score;
	else
		return profiles[prof].best_score;
}

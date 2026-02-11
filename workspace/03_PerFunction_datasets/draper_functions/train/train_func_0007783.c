put_score()
{
	if(score_changed)
	{
		static char s[32];
		snprintf(s, 16, "%010d", score);
		dscore->text(s);
		dscore->on();
		if(score > scorefile.highscore())
		{
			dhigh->text(s);
			dhigh->on();
		}
		score_changed = 0;
	}
	if(flush_score_count > 0)
		flush_score();
}

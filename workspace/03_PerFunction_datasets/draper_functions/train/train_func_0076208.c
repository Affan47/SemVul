top10_validate_stat (Statistics * stat)
{

	if (stat->score > 10.0 || stat->score < 0.0)
	{
		g_message ("Invalid score (%g): it must be between 0 and 10", stat->score);
		return (FALSE);
	}

	if ((stat->score - top10_calc_score (stat) > 1.0e-5) && (stat->score - top10_calc_score_old (stat) > 1.0e-5))
	{
		g_message ("Invalid score (%g): did you try to edit the scores file?", stat->score);
		return (FALSE);
	}

	if (stat->fluid > 95)
	{
		g_message
			("Invalid score (fluidness = %g): robots shouldn't compete with humans...",
			 stat->fluid);
		return (FALSE);
	}

	return (TRUE);
}

should_use_cash_to_capture()
{


	return military_rank_rating() < 50+pref_peacefulness/5 &&
			 ai_should_spend(pref_loyalty_concern/4);
}

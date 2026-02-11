consider_accept_surrender_request(TalkMsg* talkMsg)
{
	Nation* nationPtr = nation_array[talkMsg->from_nation_recno];
	int    offeredAmt = talkMsg->talk_para1 * 10;


	if( !nationPtr->is_ai() && config.ai_aggressiveness >= OPTION_HIGH )
	{
		if( nation_array.max_overall_nation_recno == nationPtr->nation_recno )
			return 0;
	}


	if( !(cash < 100 && profit_365days() < 0) )
	{


		if( nationPtr->overall_rank_rating() < overall_rank_rating() )
			return 0;


		if( overall_rank_rating() > 30 + pref_peacefulness/4 )
			return 0;


		if( offeredAmt < cash * (75+pref_cash_reserve/2) / 100 )
			return 0;


		if( nation_array.nation_count == 2 )
		{
			if( overall_rank_rating() > 20 - 10 * pref_military_courage / 100 )
				return 0;
		}
	}


	int surrenderToRating = ai_surrender_to_rating(talkMsg->from_nation_recno);

	surrenderToRating += 100 * offeredAmt / 13000;

	int acceptRating = overall_rank_rating()*13 + 100;


	switch( config.ai_aggressiveness )
	{
		case OPTION_HIGH:
			if( nationPtr->is_ai() )
				acceptRating -= 75;
			else
				acceptRating += 75;
			break;

		case OPTION_VERY_HIGH:
			if( nationPtr->is_ai() )
				acceptRating -= 150;
			else
				acceptRating += 150;
			break;
	}

	return surrenderToRating > acceptRating;
}

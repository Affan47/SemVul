consider_give_aid(TalkMsg* talkMsg)
{


	NationRelation* nationRelation = get_relation(talkMsg->from_nation_recno);

	if( info.game_date <
		 nationRelation->last_talk_reject_date_array[TALK_GIVE_AID-1]
		 + 365 - pref_allying_tendency )
	{
		return 0;
	}


	int importanceRating = (int) nationRelation->good_relation_duration_rating;

	if( nationRelation->status >= NATION_FRIENDLY &&
		 ai_should_spend( importanceRating, talkMsg->talk_para1 ) )
	{
		if( info.game_date > nationRelation->last_change_status_date
			 + 720 - pref_allying_tendency )
		{
			nationRelation->last_talk_reject_date_array[TALK_GIVE_AID-1] = info.game_date;
			return 1;
		}
	}

	return 0;
}

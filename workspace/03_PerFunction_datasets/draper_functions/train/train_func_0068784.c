ai_improve_relation()
{
	NationRelation* nationRelation;

	for( int i=nation_array.size() ; i>0 ; i-- )
	{
		if( nation_array.is_deleted(i) )
			continue;

		nationRelation = get_relation(i);

		if( nationRelation->status == NATION_HOSTILE )
			continue;


		change_ai_relation_level( i, trade_rating(i) / 10 );


		if( nationRelation->started_war_on_us_count > 0
			 && misc.random(5-pref_forgiveness/20) > 0 )
		{
			nationRelation->started_war_on_us_count--;
		}
	}
}

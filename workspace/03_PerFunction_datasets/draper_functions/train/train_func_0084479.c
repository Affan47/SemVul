think_new_research()
{
	TechInfo* techInfo;
	int		 bestTechId=0, curRating, bestRating=0;

	for( int techId=tech_res.tech_count ; techId>0 ; techId-- )
	{
		techInfo = tech_res[techId];

		if( techInfo->can_research(nation_recno) )
		{
			curRating = 100 + techInfo->is_nation_researching(nation_recno)*20;

			if( curRating > bestRating ||
				 ( curRating==bestRating && misc.random(2)==0 ) )
			{
				bestTechId = techId;
				bestRating = curRating;
			}
		}
	}


	if( bestTechId )
		start_research( bestTechId, COMMAND_AI );
}

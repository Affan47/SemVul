set_nation_tech_level(int nationRecno, int techLevel)
{
	err_when( nationRecno<1 || nationRecno>nation_array.size() );
	err_when( techLevel > max_tech_level );

	nation_tech_level_array[nationRecno-1] = techLevel;

	if( unit_id )
		unit_res[unit_id]->set_nation_tech_level( nationRecno, techLevel );

	else if( firm_id )
		firm_res[firm_id]->set_nation_tech_level( nationRecno, techLevel );


	if( techLevel == max_tech_level && is_nation_researching(nationRecno) > 0 )
	{


		Firm* firmPtr;

		for( int i=firm_array.size() ; i>0 ; i-- )
		{
			if( firm_array.is_deleted(i) )
				continue;

			firmPtr = firm_array[i];

			if( firmPtr->firm_id == FIRM_RESEARCH &&
				 firmPtr->nation_recno == nationRecno &&
				 ((FirmResearch*)firmPtr)->tech_id == tech_id )
			{
				((FirmResearch*)firmPtr)->terminate_research();
			}
		}
	}
}

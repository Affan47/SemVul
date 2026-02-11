ai_update_link_status()
{
	err_when( firm_id == FIRM_CAMP );

	if( !worker_array )
		return;

	if( is_worker_full() )
		return;


	Nation* ownNation = nation_array[nation_recno];
	int	  i, rc;

	for( i=0 ; i<linked_town_count ; i++ )
	{
		Town* townPtr = town_array[linked_town_array[i]];


		rc = townPtr->nation_recno==0 ||
			  ownNation->get_relation_status(townPtr->nation_recno) >= NATION_FRIENDLY;

		toggle_town_link( i+1, rc, COMMAND_AI );
	}
}

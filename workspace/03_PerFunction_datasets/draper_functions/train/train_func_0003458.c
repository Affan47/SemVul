nation_filter(int recNo)
{
	int    	i, nationCount=0;
	Nation*  viewingNation = nation_array[info.viewing_nation_recno];

	for( i=1 ; i<=nation_array.size() ; i++ )
	{
		if( nation_array.is_deleted(i) )
			continue;

		if( i==info.viewing_nation_recno ||
			 viewingNation->get_relation(i)->has_contact )
		{
			nationCount++;
		}

		if( recNo && nationCount==recNo )
			return i;
	}

	err_when( recNo );

	return nationCount;
}

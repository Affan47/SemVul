find_town_spy(int townRecno, int raceId, int spySeq)
{
	int  spyCount=size(), matchCount=0;
	Spy* spyPtr;

	for( int i=1 ; i<=spyCount ; i++ )
	{
		if( spy_array.is_deleted(i) )
			continue;

		spyPtr = spy_array[i];

		if( spyPtr->spy_place==SPY_TOWN &&
			 spyPtr->spy_place_para==townRecno &&
			 spyPtr->race_id==raceId )
		{

			if( ++matchCount == spySeq )
				return i;
		}
	}

	return 0;
}

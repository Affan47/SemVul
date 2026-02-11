is_market_linked_to_town(int ownBaseTownOnly)
{
	Town* townPtr;

	for(int i=0 ; i<linked_town_count ; i++ )
	{
		if( linked_town_enable_array[i] != LINK_EE )
			continue;

		if( ownBaseTownOnly )
		{
			townPtr = town_array[ linked_town_array[i] ];

			if( townPtr->nation_recno == nation_recno &&
				 townPtr->is_base_town )
			{
				return 1;
			}
		}
		else
		{
			return 1;
		}
	}

	return 0;
}

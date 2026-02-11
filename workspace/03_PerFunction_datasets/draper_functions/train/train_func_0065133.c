max_human_battle_ship_count()
{


	Unit* unitPtr;
	short nationShipCountArray[MAX_NATION];

	memset( nationShipCountArray, 0, sizeof(nationShipCountArray) );

	int i;
	for( i=unit_array.size() ; i>0 ; i-- )
	{
		if( unit_array.is_deleted(i) )
			continue;

		unitPtr = unit_array[i];

		if( unitPtr->unit_id != UNIT_CARAVEL &&
			 unitPtr->unit_id != UNIT_GALLEON )
		{
			continue;
		}

		err_when( unitPtr->nation_recno < 1 || unitPtr->nation_recno > MAX_NATION );

		nationShipCountArray[unitPtr->nation_recno-1]++;
	}


	int maxShipCount=0;

	for( i=nation_array.size() ; i>0 ; i-- )
	{
		if( nation_array.is_deleted(i) )
			continue;

		if( nation_array[i]->is_ai() )
			continue;


		if( nationShipCountArray[i-1] > maxShipCount )
		{
			maxShipCount = nationShipCountArray[i-1];
		}
	}

	return maxShipCount;
}

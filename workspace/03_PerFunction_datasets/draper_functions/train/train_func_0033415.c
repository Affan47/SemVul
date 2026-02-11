execute_new_action()
{


	short* rebelRecnoArray = (short*) mem_add( mobile_rebel_count * sizeof(short) );
	Unit*  unitPtr;
	int	 rebelCount=0;

	#ifdef DEBUG
		int dieUnit = 0;
	#endif

	for( int i=unit_array.size() ; i>=1 ; i-- )
	{
		if( unit_array.is_deleted(i) )
		{
			#ifdef DEBUG
				if(!unit_array.SpriteArray::is_deleted(i))
					dieUnit++;
			#endif

			continue;
		}

		unitPtr = unit_array[i];

		if( unitPtr->unit_mode == UNIT_MODE_REBEL &&
			 unitPtr->unit_mode_para == rebel_recno )
		{
			err_when( rebelCount >= mobile_rebel_count );

			rebelRecnoArray[rebelCount++] = i;
		}
	}

#ifdef DEBUG
	if(rebelCount+dieUnit != mobile_rebel_count)
		int debug = 0;
#endif

	if( !rebelCount )
	{
		mem_del( rebelRecnoArray );
		return;
	}


	Town* townPtr;
	Firm* firmPtr;

	switch( action_mode )
	{
		case REBEL_ATTACK_TOWN:
			err_when( town_array.is_deleted(action_para) || town_array[action_para]->nation_recno==0 );

			townPtr = town_array[action_para];

			unit_array.attack( townPtr->loc_x1, townPtr->loc_y1, 0, rebelRecnoArray, rebelCount, COMMAND_AI, 0 );

			break;

		case REBEL_ATTACK_FIRM:
			err_when( firm_array.is_deleted(action_para) || firm_array[action_para]->nation_recno==0 );

			firmPtr = firm_array[action_para];

			unit_array.attack( firmPtr->loc_x1, firmPtr->loc_y1, 0, rebelRecnoArray, rebelCount, COMMAND_AI, 0 );

			break;

		case REBEL_SETTLE_NEW:
			unit_array.settle( action_para, action_para2, 0, 1, rebelRecnoArray, rebelCount );
			break;

		case REBEL_SETTLE_TO:
			unit_array.assign( action_para, action_para2, 0, 1, rebelRecnoArray, rebelCount);
			break;
	}

	mem_del( rebelRecnoArray );
}

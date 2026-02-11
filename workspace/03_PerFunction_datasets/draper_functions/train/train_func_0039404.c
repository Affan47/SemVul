add_soldier(int generalUnitRecno)
{


	for( int i=0 ; i<monster_general_count ; i++ )
	{
		if( monster_general_array[i].mobile_unit_recno == generalUnitRecno )
		{
			if(monster_general_array[i].soldier_count>=MAX_SOLDIER_PER_GENERAL)
				return;

			monster_general_array[i].soldier_count++;
			return;
		}
	}


	if( waiting_soldier_count < MAX_WAITING_SOLDIER )
	{
		waiting_soldier_array[waiting_soldier_count++] = generalUnitRecno;
	}
}

init_active_monster()
{
	int monsterId;
	int activeCount=0;
	int loopCount=0;


	memset( active_monster_array, 0, sizeof(active_monster_array) );


	#ifdef DEMO

	active_monster_array[0] = 4;
	active_monster_array[1] = 11;
	active_monster_array[2] = 12;

	#endif


	while(1)
	{
		err_when( ++loopCount > 1000 );

		monsterId = misc.random(monster_count)+1;


		int i;
		for( i=0 ; i<activeCount ; i++ )
		{
			if( active_monster_array[i] == monsterId )
				break;
		}


		if( i==activeCount )
		{
			active_monster_array[activeCount] = monsterId;

			if( ++activeCount == MAX_ACTIVE_MONSTER )
				return;
		}
	}
}

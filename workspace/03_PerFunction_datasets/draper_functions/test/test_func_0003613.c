plant_init()
{
	plant_count = 0;
	int trial;
	for(trial = 50; trial > 0; --trial)
		{

		int y = 1+misc.random(max_y_loc-2);
		int x = 1+misc.random(max_x_loc-2);

		Location *l = get_loc(x,y);
		int build_flag = TRUE;
		char teraType = terrain_res[l->terrain_id]->average_type;


		for( int y1 = y-1; y1 <= y+1; ++y1)
			for( int x1 = x-1; x1 <= x+1; ++x1)
			{
				l = get_loc(x1,y1);

				if( !l->can_add_plant() || terrain_res[l->terrain_id]->average_type != teraType)
					build_flag = FALSE;

			}

		if( build_flag )
		{
			short plantBitmap = plant_res.scan( 0, teraType, 0);
			short plantArray[PLANT_ARRAY_SIZE];
			for( int i = 0; i < PLANT_ARRAY_SIZE; ++i)
			{
				plantArray[i] = plant_res.plant_recno(plant_res.scan(0, teraType, 0));
			}
			if( plantArray[0] )
			{
				plant_spray(plantArray, 6+misc.random(4), x, y);
			}
		}
	}

	plant_limit = plant_count * 3 / 2;


	for(trial = 8; trial > 0; --trial)
	{
		plant_death(2);
	}
}

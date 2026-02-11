cave_temp_room_unlight(void)
{
	int i;


	for (i = 0; i < temp_n; i++)
	{
		int y = temp_y[i];
		int x = temp_x[i];


		cave_info[y][x] &= ~(CAVE_TEMP);


		cave_info[y][x] &= ~(CAVE_GLOW);


		if (cave_feat[y][x] <= FEAT_INVIS)
		{

			cave_info[y][x] &= ~(CAVE_MARK);
		}
	}


	p_ptr->update |= (PU_FORGET_VIEW | PU_UPDATE_VIEW | PU_MONSTERS);


	update_stuff();


	for (i = 0; i < temp_n; i++)
	{
		int y = temp_y[i];
		int x = temp_x[i];


		light_spot(y, x);
	}


	temp_n = 0;
}

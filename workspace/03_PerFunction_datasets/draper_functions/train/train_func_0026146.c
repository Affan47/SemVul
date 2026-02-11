light_room(int y1, int x1)
{
	int i, x, y;


        temp_n = 0;

	cave_temp_room_aux(y1, x1);


	for (i = 0; i < temp_n; i++)
	{
		x = temp_x[i], y = temp_y[i];


		if (!cave_floor_bold(y, x)) continue;


		cave_temp_room_aux(y + 1, x);
		cave_temp_room_aux(y - 1, x);
		cave_temp_room_aux(y, x + 1);
		cave_temp_room_aux(y, x - 1);


		cave_temp_room_aux(y + 1, x + 1);
		cave_temp_room_aux(y - 1, x - 1);
		cave_temp_room_aux(y - 1, x + 1);
		cave_temp_room_aux(y + 1, x - 1);
	}


	cave_temp_room_light();
}

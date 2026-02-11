light_room(int y1, int x1, bool light)
{
	int i, x, y;
	struct point_set *ps;

	ps = point_set_new(200);

	cave_room_aux(ps, y1, x1);


	for (i = 0; i < ps->n; i++)
	{
		x = ps->pts[i].x, y = ps->pts[i].y;


		if (!cave_floor_bold(y, x)) continue;


		cave_room_aux(ps, y + 1, x);
		cave_room_aux(ps, y - 1, x);
		cave_room_aux(ps, y, x + 1);
		cave_room_aux(ps, y, x - 1);


		cave_room_aux(ps, y + 1, x + 1);
		cave_room_aux(ps, y - 1, x - 1);
		cave_room_aux(ps, y - 1, x + 1);
		cave_room_aux(ps, y + 1, x - 1);
	}


	if (light) {
		cave_light(ps);
	} else {
		cave_unlight(ps);
	}
	point_set_dispose(ps);
}

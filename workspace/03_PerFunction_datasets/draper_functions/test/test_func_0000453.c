glue_obstacle(level *lvl, obstacle *o)
{
	int x_min, x_max, x;
	int y_min, y_max, y;
	int idx;

	if (o->type == -1)
		return;

	obstacle_boundaries(o, &x_min, &x_max, &y_min, &y_max);

	idx = get_obstacle_index(lvl, o);

	for (x = x_min; x <= x_max; x++) {
		for (y = y_min; y <= y_max; y++) {
			if (x < 0 || y < 0 || x >= lvl->xlen || y >= lvl->ylen)
				continue;

			dynarray_add(&lvl->map[y][x].glued_obstacles, &idx, sizeof(idx));
		}
	}
}

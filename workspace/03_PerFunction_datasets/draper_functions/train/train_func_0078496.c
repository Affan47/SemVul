action_create_waypoint(level *EditLevel, int x, int y, int random_spawn)
{
	waypoint *wpts = EditLevel->waypoints.arr;
	int wpnum;

	wpnum = get_waypoint(EditLevel, x, y);
	if (wpnum < 0) {

		wpnum = add_waypoint(EditLevel, x, y, random_spawn);


		wpts = EditLevel->waypoints.arr;


		action_push(ACT_REMOVE_WAYPOINT, wpts[wpnum].x, wpts[wpnum].y);
	}

	return &wpts[wpnum];
}

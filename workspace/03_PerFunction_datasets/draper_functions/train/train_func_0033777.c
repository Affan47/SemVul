g_robot_grab(GRobot *robot)
{
	gint x_to, y_to;
	gint dx, dy;

	g_return_val_if_fail(robot->ui != NULL && robot->map != NULL, FALSE);


	switch (robot->dir)
	{
	case NORTH:
		dx = 0;
		dy = -1;
		break;
	case EAST:
		dx = 1;
		dy = 0;
		break;
	case SOUTH:
		dx = 0;
		dy = 1;
		break;
	case WEST:
		dx = -1;
		dy = 0;
		break;
	}


	x_to = robot->x + dx;
	y_to = robot->y + dy;

	robot->energy -= 5;
	if (robot->energy < 1)
	{
		g_signal_emit(robot, g_robot_signals[DEATH], 0);
	}

	gdk_threads_enter();
	ui_arena_robot_grab(robot->ui, robot->x, robot->y, robot->dir, x_to,
		y_to, robot->energy, robot->score, robot->shields);
	gdk_threads_leave();


	switch (MAP_GET_OBJECT(robot->map, x_to, y_to))
	{
	case SPACE:
	case WALL:
	case ROBOT:
		return FALSE;
		break;

	case BADDIE:
		robot->shields -= 10;
		if (robot->shields < 1)
		{
			g_signal_emit(robot, g_robot_signals[DEATH], 0);
		}
		return (FALSE);

	case FOOD:

		robot->energy += 15;
		break;

	case PRIZE:
		robot->score++;
		break;
	}


	MAP_SET_OBJECT(robot->map, x_to, y_to, SPACE);
	gdk_threads_enter();
	ui_arena_add_thing(robot->ui, x_to, y_to, SPACE);
	gdk_threads_leave();

	return TRUE;
}

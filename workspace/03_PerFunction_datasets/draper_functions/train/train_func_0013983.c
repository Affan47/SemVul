state_machine_select_new_waypoint(enemy * ThisRobot, moderately_finepoint * new_move_target)
{

	new_move_target->x = ThisRobot->pos.x;
	new_move_target->y = ThisRobot->pos.y;


	if (!set_new_random_waypoint(ThisRobot)) {
		ThisRobot->combat_state = WAYPOINTLESS_WANDERING;
	} else {
		ThisRobot->combat_state = TURN_TOWARDS_NEXT_WAYPOINT;
	}
}

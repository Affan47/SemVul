state_machine_rush_tux_and_open_talk(enemy * ThisRobot, moderately_finepoint * new_move_target)
{

	if (ThisRobot->pos.z == Me.pos.z) {
		new_move_target->x = Me.pos.x;
		new_move_target->y = Me.pos.y;
	} else {
		new_move_target->x = ThisRobot->pos.x;
		new_move_target->y = ThisRobot->pos.y;
	}


	if (sqrt((ThisRobot->virt_pos.x - Me.pos.x) * (ThisRobot->virt_pos.x - Me.pos.x) + (ThisRobot->virt_pos.y - Me.pos.y) * (ThisRobot->virt_pos.y - Me.pos.y)) < 1) {
		ChatWithFriendlyDroid(ThisRobot);
		ThisRobot->will_rush_tux = FALSE;
		ThisRobot->combat_state = SELECT_NEW_WAYPOINT;
		return;
	}
}

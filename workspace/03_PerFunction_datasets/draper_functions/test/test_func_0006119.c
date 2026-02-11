MoveThisRobotTowardsHisCurrentTarget(enemy *ThisRobot)
{
	if (ThisRobot->animation_type == ATTACK_ANIMATION)
		return;

	if ((ThisRobot->PrivatePathway[0].x == ThisRobot->pos.x) && (ThisRobot->PrivatePathway[0].y == ThisRobot->pos.y)) {
		if (ThisRobot->PrivatePathway[1].x != -1) {
			int i;
			for (i = 1; i < 5; i++) {
				ThisRobot->PrivatePathway[i - 1].x = ThisRobot->PrivatePathway[i].x;
				ThisRobot->PrivatePathway[i - 1].y = ThisRobot->PrivatePathway[i].y;
			}
			ThisRobot->PrivatePathway[4].x = -1;
			ThisRobot->PrivatePathway[4].y = -1;
		}
		return;
	}

	move_enemy_to_spot(ThisRobot, ThisRobot->PrivatePathway[0]);

	if ((fabsf(ThisRobot->pos.x - ThisRobot->PrivatePathway[0].x) < 0.001)
	    && fabsf(ThisRobot->pos.y - ThisRobot->PrivatePathway[0].y) < 0.001) {
		int i;
		for (i = 1; i < 5; i++) {
			ThisRobot->PrivatePathway[i - 1].x = ThisRobot->PrivatePathway[i].x;
			ThisRobot->PrivatePathway[i - 1].y = ThisRobot->PrivatePathway[i].y;
		}
		ThisRobot->PrivatePathway[4].x = -1;
		ThisRobot->PrivatePathway[4].y = -1;
	}

	if (ThisRobot->PrivatePathway[0].x == -1) {
		ThisRobot->PrivatePathway[0].x = ThisRobot->pos.x;
		ThisRobot->PrivatePathway[0].y = ThisRobot->pos.y;
	}
}

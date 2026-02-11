MoveAwayFromMeleeCombat(Enemy ThisRobot, moderately_finepoint * set_move_tgt)
{
	finepoint VictimPosition = { 0.0, 0.0 };
	finepoint CurrentPosition = { 0.0, 0.0 };
	moderately_finepoint StepVector;
	moderately_finepoint RotatedStepVector;
	float StepVectorLen;
	int i;

#define ANGLES_TO_TRY 7
	float RotationAngleTryList[ANGLES_TO_TRY] = { 0, 30, 360 - 30, 60, 360 - 60, 90, 360 - 90 };

	VictimPosition.x = enemy_get_target_position(ThisRobot)->x;
	VictimPosition.y = enemy_get_target_position(ThisRobot)->y;

	CurrentPosition.x = ThisRobot->virt_pos.x;
	CurrentPosition.y = ThisRobot->virt_pos.y;

	StepVector.x = VictimPosition.x - CurrentPosition.x;
	StepVector.y = VictimPosition.y - CurrentPosition.y;


	if ((fabsf(StepVector.x) < 0.01) && (fabsf(StepVector.y) < 0.01)) {
		if (MyRandom(1) == 1) {
			StepVector.x = 1.0;
			StepVector.y = 1.0;
		} else {
			StepVector.x = -1.0;
			StepVector.y = -1.0;
		}
	}

	StepVectorLen = sqrt((StepVector.x) * (StepVector.x) + (StepVector.y) * (StepVector.y));

	StepVector.x /= (-1 * StepVectorLen);
	StepVector.y /= (-1 * StepVectorLen);

	for (i = 0; i < ANGLES_TO_TRY; i++) {
		RotatedStepVector.x = StepVector.x;
		RotatedStepVector.y = StepVector.y;
		RotateVectorByAngle(&RotatedStepVector, RotationAngleTryList[i]);


		if (  ConsideredMoveIsFeasible(ThisRobot, RotatedStepVector) &&
		    DirectLineColldet(ThisRobot->virt_pos.x + RotatedStepVector.x, ThisRobot->virt_pos.y + RotatedStepVector.y,
				      VictimPosition.x, VictimPosition.y, ThisRobot->pos.z, NULL)
		    ) {
			set_move_tgt->x = ThisRobot->pos.x + RotatedStepVector.x;
			set_move_tgt->y = ThisRobot->pos.y + RotatedStepVector.y;
			break;
		}

		set_move_tgt->x = ThisRobot->pos.x;
		set_move_tgt->y = ThisRobot->pos.y;

	}
}

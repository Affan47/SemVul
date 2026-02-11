set_rotation_index_for_this_robot(enemy * ThisRobot)
{
	int RotationIndex;


	RotationIndex = ((ThisRobot->current_angle - 45.0 + 360.0 + 360 /
			  (2 * ROTATION_ANGLES_PER_ROTATION_MODEL)) * ROTATION_ANGLES_PER_ROTATION_MODEL / 360);


	while (RotationIndex < 0)
		RotationIndex += ROTATION_ANGLES_PER_ROTATION_MODEL;
	while (RotationIndex >= ROTATION_ANGLES_PER_ROTATION_MODEL)
		RotationIndex -= ROTATION_ANGLES_PER_ROTATION_MODEL;


	if (RotationIndex == ThisRobot->previous_phase) {
		ThisRobot->last_phase_change += Frame_Time();
	} else {
		if (ThisRobot->last_phase_change >= WAIT_BEFORE_ROTATE) {
			ThisRobot->last_phase_change = 0.0;
			ThisRobot->previous_phase = RotationIndex;
		} else {


			RotationIndex = ThisRobot->previous_phase;
			ThisRobot->last_phase_change += Frame_Time();
		}
	}


	return (RotationIndex);

}

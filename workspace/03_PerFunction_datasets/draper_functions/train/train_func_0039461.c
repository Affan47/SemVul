startNextMove (int speed)
{

    Move * move  = moves.at (moveIndex);
    Rotation rot = move->direction;

    if (undoing && (rot != ONE_EIGHTY)) {
	rot = (rot == CLOCKWISE) ? ANTICLOCKWISE : CLOCKWISE;
    }
    cube->moveSlice (move->axis, move->slice, rot);


    moveAngleMax  = 0;
    moveAngleStep = 0;
    moveAngle     = 0;

    if (movesToDo <= 0) {

	return;
    }

    if (undoing) {
	--moveIndex;
    }
    else {
	++moveIndex;
    }
    move = moves.at (moveIndex);

    cube->setMoveInProgress (move->axis, move->slice);
    cube->setMoveAngle (0);
    startAnimatedMove (move, speed);
}

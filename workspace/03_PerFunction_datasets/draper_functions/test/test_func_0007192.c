appendMove (Move * move)
{
    move->degrees        = 90;


    if ((move->slice != WHOLE_CUBE) &&
	(cubeSize [(move->axis+1)%nAxes] != cubeSize [(move->axis+2)%nAxes])) {
	move->degrees = 180;
    }


    moves.append (move);
}

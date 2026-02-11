getOutgoingPosition( int position[DIM_MAX], int incomingDirection[DIM_MAX], QList<int> &points)
{
	int outgoingDirection[DIM_MAX];

	int nextPosition[DIM_MAX];
	nextPosition[DIM_X] = position[DIM_X] + incomingDirection[DIM_X];
	nextPosition[DIM_Y] = position[DIM_Y] + incomingDirection[DIM_Y];

	int nextLeftPosition[DIM_MAX];
	nextLeftPosition[DIM_X] = nextPosition[DIM_X] + incomingDirection[DIM_Y];
	nextLeftPosition[DIM_Y] = nextPosition[DIM_Y] + incomingDirection[DIM_X];

	int nextRightPosition[DIM_MAX];
	nextRightPosition[DIM_X] = nextPosition[DIM_X] - incomingDirection[DIM_Y];
	nextRightPosition[DIM_Y] = nextPosition[DIM_Y] - incomingDirection[DIM_X];

	bool deviation = false;
	if (positionInTheBox(nextPosition) && contains((nextPosition[DIM_X] - 2) + (nextPosition[DIM_Y] - 2) * m_columns)) {

		position[DIM_X] = KBBGameDoc::HIT_POSITION;
		position[DIM_Y] = KBBGameDoc::HIT_POSITION;
		points.append(absolutePositionToBoxPosition(nextPosition));
	} else if (positionInTheBox(nextLeftPosition) && contains((nextLeftPosition[DIM_X] - 2) + (nextLeftPosition[DIM_Y] - 2) * m_columns)) {

		outgoingDirection[DIM_X] = -incomingDirection[DIM_Y];
		outgoingDirection[DIM_Y] = -incomingDirection[DIM_X];
		deviation = true;
	} else if (positionInTheBox(nextRightPosition) && contains((nextRightPosition[DIM_X] - 2) + (nextRightPosition[DIM_Y] - 2) * m_columns)) {

		outgoingDirection[DIM_X] = incomingDirection[DIM_Y];
		outgoingDirection[DIM_Y] = incomingDirection[DIM_X];
		deviation = true;
	} else {

		position[DIM_X] = nextPosition[DIM_X];
		position[DIM_Y] = nextPosition[DIM_Y];
		outgoingDirection[DIM_X] = incomingDirection[DIM_X];
		outgoingDirection[DIM_Y] = incomingDirection[DIM_Y];
	}


	if (positionInTheBox(position)) {
		points.append(absolutePositionToBoxPosition(position));
		getOutgoingPosition( position, outgoingDirection, points );
	} else if (deviation)

		points.append(absolutePositionToBoxPosition(nextPosition));

	return;
}

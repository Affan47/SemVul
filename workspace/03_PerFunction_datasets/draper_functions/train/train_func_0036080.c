getSegmentEnd() const
{
	if (vertexIndex < getLine()->getNumPoints() - 1)
		return currentLine->getCoordinateN(vertexIndex + 1);
	Coordinate c;
	c.setNull();
	return c;
}

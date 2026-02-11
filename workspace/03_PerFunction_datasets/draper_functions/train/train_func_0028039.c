matchInSameDirection(const Coordinate& p0, const Coordinate& p1,
		const Coordinate& ep0, const Coordinate& ep1)
{
	if (!(p0==ep0))
		return false;

	if (CGAlgorithms::computeOrientation(p0,p1,ep1)==CGAlgorithms::COLLINEAR
		&& Quadrant::quadrant(p0,p1)==Quadrant::quadrant(ep0,ep1))
			return true;
	return false;
}

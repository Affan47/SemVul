isCoveredByLA(const Coordinate& coord)
{
	if (isCovered(coord,resultLineList)) return true;
	if (isCovered(coord,resultPolyList)) return true;
	return false;
}

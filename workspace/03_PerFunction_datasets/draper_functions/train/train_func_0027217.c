isDeletable(int i0, int i1, int i2,
                                       double distanceTol) const
{
	const Coordinate& p0 = inputLine[i0];
	const Coordinate& p1 = inputLine[i1];
	const Coordinate& p2 = inputLine[i2];

	if (! isConcave(p0, p1, p2)) return false;
	if (! isShallow(p0, p1, p2, distanceTol)) return false;


	return isShallowSampled(p0, p1, i0, i2, distanceTol);
}

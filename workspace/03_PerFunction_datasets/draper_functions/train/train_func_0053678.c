locate(const Coordinate& p, const LineString *l)
{
	const CoordinateSequence* pt=l->getCoordinatesRO();
	if (! l->isClosed()) {
		if ((p==pt->getAt(0)) || (p==pt->getAt(pt->getSize()-1))) {
			return Location::BOUNDARY;
		}
	}
	if (CGAlgorithms::isOnLine(p,pt))
		return Location::INTERIOR;
	return Location::EXTERIOR;
}

isOnEdge(const QuadEdge &e, const Coordinate &p) const
{
	geom::LineSegment seg;
	seg.setCoordinates(e.orig().getCoordinate(), e.dest().getCoordinate());
	double dist = seg.distance(p);

	return dist < edgeCoincidenceTolerance;
}

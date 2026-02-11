getSegmentLength(const Geometry* linearGeom) const
{
	const LineString* lineComp = dynamic_cast<const LineString*> (linearGeom->getGeometryN(componentIndex));


	unsigned int segIndex = segmentIndex;
	if (segmentIndex >= lineComp->getNumPoints() - 1)
		segIndex = lineComp->getNumPoints() - 2;

	Coordinate p0 = lineComp->getCoordinateN(segIndex);
	Coordinate p1 = lineComp->getCoordinateN(segIndex + 1);
	return p0.distance(p1);
}

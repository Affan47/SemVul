isSimpleLinearGeometry(const Geometry *geom)
{
	if (geom->isEmpty()) return true;
	GeometryGraph graph(0,geom);
	LineIntersector li;
	std::auto_ptr<SegmentIntersector> si (graph.computeSelfNodes(&li,true));


	if (!si->hasIntersection()) return true;

	if (si->hasProperIntersection())
	{
		nonSimpleLocation.reset(
			new Coordinate(si->getProperIntersectionPoint())
		);
		return false;
	}

	if (hasNonEndpointIntersection(graph)) return false;

	if ( isClosedEndpointsInInterior ) {
		if (hasClosedEndpointIntersection(graph)) return false;
	}

	return true;
}

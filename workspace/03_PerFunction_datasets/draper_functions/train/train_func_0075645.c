labelIncompleteNode(Node *n, int targetIndex)
{
#if GEOS_DEBUG
	cerr<<"OverlayOp::labelIncompleteNode("<<n->print()<<", "<<targetIndex<<")"<<endl;
#endif
	const Geometry *targetGeom = arg[targetIndex]->getGeometry();
	int loc=ptLocator.locate(n->getCoordinate(), targetGeom);
	n->getLabel().setLocation(targetIndex, loc);

#if GEOS_DEBUG
	cerr<<"   after location set: "<<n->print()<<endl;
#endif

#if COMPUTE_Z


	const LineString *line = dynamic_cast<const LineString *>(targetGeom);
	if ( loc == Location::INTERIOR && line )
	{
		mergeZ(n, line);
	}
	const Polygon *poly = dynamic_cast<const Polygon *>(targetGeom);
	if ( loc == Location::BOUNDARY && poly )
	{
		mergeZ(n, poly);
	}
#if USE_INPUT_AVGZ
	if ( loc == Location::INTERIOR && poly )
	{
		n->addZ(getAverageZ(targetIndex));
	}
#endif
#endif
}

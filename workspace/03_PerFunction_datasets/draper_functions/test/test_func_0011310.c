checkCollapses(const SegmentString& ss) const
{
	const CoordinateSequence& pts = *(ss.getCoordinates());
	for (unsigned int i=0, n=pts.getSize()-2; i<n; ++i)
	{
		checkCollapse(pts[i], pts[i + 1], pts[i + 2]);
	}
}

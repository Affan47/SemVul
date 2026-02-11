computeVertexSnaps(NodedSegmentString* e)
{
	CoordinateSequence& pts0 = *(e->getCoordinates());
	for (unsigned int i=0, n=pts0.size()-1; i<n; ++i)
	{
		HotPixel hotPixel(pts0[i], scaleFactor, li);
		bool isNodeAdded = pointSnapper->snap(hotPixel, e, i);

		if (isNodeAdded) {
			e->addIntersection(pts0[i], i);
		}
	}
}

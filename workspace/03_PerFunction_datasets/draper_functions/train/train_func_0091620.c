node(vector<SegmentString*> *segStrings,
		int *numInteriorIntersections)
{
	IntersectionAdder si(li);
	MCIndexNoder noder;
	noder.setSegmentIntersector(&si);
	noder.computeNodes(segStrings);
	nodedSegStrings = noder.getNodedSubstrings();
	*numInteriorIntersections = si.numInteriorIntersections;

}

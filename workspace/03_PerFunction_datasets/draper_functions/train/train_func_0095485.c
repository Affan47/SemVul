addCurves(const std::vector<CoordinateSequence*>& lineList,
	int leftLoc, int rightLoc)
{
	for (size_t i=0, n=lineList.size(); i<n; ++i)
	{
		CoordinateSequence *coords = lineList[i];
		addCurve(coords, leftLoc, rightLoc);
	}
}

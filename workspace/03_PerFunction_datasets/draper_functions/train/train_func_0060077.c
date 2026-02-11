findAndClassifyIntersections(const geom::Geometry* geom)
{
	noding::SegmentString::ConstVect lineSegStr;
	noding::SegmentStringUtil::extractSegmentStrings(geom, lineSegStr);

	algorithm::LineIntersector li;

	noding::SegmentIntersectionDetector intDetector(&li);

	intDetector.setFindAllIntersectionTypes(true);
	prepPoly->getIntersectionFinder()->intersects(&lineSegStr, &intDetector);

	hasSegmentIntersection = intDetector.hasIntersection();
	hasProperIntersection = intDetector.hasProperIntersection();
	hasNonProperIntersection = intDetector.hasNonProperIntersection();

	for (std::size_t i = 0, ni = lineSegStr.size(); i < ni; i++ )
	{
		delete lineSegStr[i];
	}
}

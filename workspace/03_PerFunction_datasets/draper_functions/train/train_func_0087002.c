containsProperly( const geom::Geometry * geom)
{


	bool isAllInPrepGeomArea = isAllTestComponentsInTargetInterior( geom);
	if ( !isAllInPrepGeomArea )
		return false;


	noding::SegmentString::ConstVect lineSegStr;
	noding::SegmentStringUtil::extractSegmentStrings( geom, lineSegStr);
	bool segsIntersect = prepPoly->getIntersectionFinder()->intersects( &lineSegStr);

	for ( size_t i = 0, ni = lineSegStr.size(); i < ni; i++ ) {
		delete lineSegStr[ i ];
	}

	if (segsIntersect)
		return false;


	if (	geom->getGeometryTypeId() == geos::geom::GEOS_MULTIPOLYGON
		||	geom->getGeometryTypeId() == geos::geom::GEOS_POLYGON )
	{

		bool isTargetGeomInTestArea = isAnyTargetComponentInAreaTest( geom, prepPoly->getRepresentativePoints());
		if (isTargetGeomInTestArea)
			return false;
	}

	return true;
}

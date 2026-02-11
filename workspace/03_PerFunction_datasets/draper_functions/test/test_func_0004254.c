addMitreJoin(const geom::Coordinate& p,
                    const geom::LineSegment& offset0,
                    const geom::LineSegment& offset1,
                    double distance)
{
  bool isMitreWithinLimit = true;
  Coordinate intPt;


    try
    {
        HCoordinate::intersection(offset0.p0, offset0.p1,
            offset1.p0, offset1.p1,
            intPt);

        double mitreRatio = distance <= 0.0 ? 1.0
            : intPt.distance(p) / fabs(distance);

        if (mitreRatio > bufParams.getMitreLimit())
            isMitreWithinLimit = false;
    }
    catch (const NotRepresentableException& e)
    {
        ::geos::ignore_unused_variable_warning(e);

        intPt = Coordinate(0,0);
        isMitreWithinLimit = false;
    }

    if (isMitreWithinLimit)
    {
        segList.addPt(intPt);
    }
    else
    {
        addLimitedMitreJoin(offset0, offset1, distance,
            bufParams.getMitreLimit());

    }
}

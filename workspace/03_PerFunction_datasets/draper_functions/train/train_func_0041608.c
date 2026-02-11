computeDistance(const geom::Geometry& geom,
                                          const geom::Coordinate& pt,
                                          PointPairDistance& ptDist)
{
	if ( const LineString* ls = dynamic_cast<const LineString*>(&geom) )
	{
		computeDistance(*ls, pt, ptDist);
	}
	else if ( const Polygon* pl = dynamic_cast<const Polygon*>(&geom) )
	{
		computeDistance(*pl, pt, ptDist);
	}
	else if ( const GeometryCollection* gc = dynamic_cast<const GeometryCollection*>(&geom) )
	{
		for (size_t i = 0; i < gc->getNumGeometries(); i++)
		{
			const Geometry* g = gc->getGeometryN(i);
			computeDistance(*g, pt, ptDist);
		}
	}
	else
	{

		ptDist.setMinimum(*(geom.getCoordinate()), pt);
	}
}

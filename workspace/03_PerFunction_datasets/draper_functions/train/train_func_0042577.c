isCovered(const Coordinate& coord,vector<Polygon*> *geomList)
{
	for(size_t i=0, n=geomList->size(); i<n; ++i)
	{
		Geometry *geom=(Geometry*)(*geomList)[i];
		int loc=ptLocator.locate(coord,geom);
		if (loc!=Location::EXTERIOR) return true;
	}
	return false;
}

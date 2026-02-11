mergeZ(Node *n, const Polygon *poly) const
{
	const LineString *ls;
	int found = 0;
	ls = poly->getExteriorRing();
	found = mergeZ(n, ls);
	if ( found ) return 1;
	for (size_t i=0, nr=poly->getNumInteriorRing(); i<nr; ++i)
	{
		ls = poly->getInteriorRingN(i);
		found = mergeZ(n, ls);
		if ( found ) return 1;
	}
	return 0;
}

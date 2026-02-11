createPolygon(LinearRing *shell, vector<Geometry *> *holes)
	const
{
	return new Polygon(shell, holes, this);
}

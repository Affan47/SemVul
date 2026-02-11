getCoordinate() const
{
	if (outEdges.empty())
		return Coordinate::getNull();
	DirectedEdge *e=outEdges[0];
	return e->getCoordinate();
}

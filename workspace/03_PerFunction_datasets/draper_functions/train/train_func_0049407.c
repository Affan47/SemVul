createNode(const Coordinate &coord) const
{
	return new RelateNode(coord, new EdgeEndBundleStar());
}

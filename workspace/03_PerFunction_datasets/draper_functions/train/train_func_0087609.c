LineString(CoordinateSequence::AutoPtr newCoords,
		const GeometryFactory *factory)
	:
	Geometry(factory),
	points(newCoords)
{
	validateConstruction();
}

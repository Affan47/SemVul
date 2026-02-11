writeCoordinateSequence(const CoordinateSequence &cs,
	bool sized)
{
	std::size_t size = cs.getSize();
	bool is3d=false;
	if ( outputDimension > 2) is3d = true;

	if (sized) writeInt(size);
	for (std::size_t i=0; i<size; i++) writeCoordinate(cs, i, is3d);
}

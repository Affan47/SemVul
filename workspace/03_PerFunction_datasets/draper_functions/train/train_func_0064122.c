appendPointText(const Coordinate* coordinate, int ,
		Writer *writer)
{
	if (coordinate==NULL) {
		writer->write("EMPTY");
	} else {
		writer->write("(");
		appendCoordinate(coordinate, writer);
		writer->write(")");
	}
}

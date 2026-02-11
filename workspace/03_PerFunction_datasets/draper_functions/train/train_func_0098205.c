appendMultiPointText(const MultiPoint *multiPoint,
		int , Writer *writer)
{
	if (multiPoint->isEmpty()) {
		writer->write("EMPTY");
	} else {
		writer->write("(");
		for (unsigned int i=0, n=multiPoint->getNumGeometries();
				i<n; i++)
		{
			if (i > 0)
			{
				writer->write(", ");
			}
			appendCoordinate(
				dynamic_cast<const Point*>(multiPoint->getGeometryN(i))->getCoordinate(),
				writer);
		}
		writer->write(")");
	}
}

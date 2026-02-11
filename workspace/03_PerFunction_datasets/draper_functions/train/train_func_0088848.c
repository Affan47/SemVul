getLength(const LinearLocation& loc) const
{
	double totalLength = 0.0;

	LinearIterator it(linearGeom);
	while (it.hasNext())
	{
		if (! it.isEndOfLine())
		{
			Coordinate p0 = it.getSegmentStart();
			Coordinate p1 = it.getSegmentEnd();
			double segLen = p1.distance(p0);

			if (loc.getComponentIndex() == it.getComponentIndex()
					&& loc.getSegmentIndex() == it.getVertexIndex())
			{
				return totalLength + segLen * loc.getSegmentFraction();
			}
			totalLength += segLen;
		}
		it.next();
	}
	return totalLength;
}

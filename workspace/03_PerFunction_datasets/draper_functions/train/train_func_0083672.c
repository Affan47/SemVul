add(const TaggedLineString& line)
{
	const vector<TaggedLineSegment*>& segs = line.getSegments();
	for (size_t i=0, n=segs.size(); i<n; ++i)
	{
		const LineSegment* seg = segs[i];
		add(seg);
	}
}

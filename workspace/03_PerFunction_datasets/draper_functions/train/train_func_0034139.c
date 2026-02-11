extractSegmentStrings(const geom::Geometry& g,
                                     SegmentString::NonConstVect& to)
{
  SegmentStringExtractor ex(to);
	g.apply_ro(&ex);
}

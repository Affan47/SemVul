Do(const Segment& in1, Segment& out)
{
	if(!mHaveInternalSegment) return false;
	return SegmentTransformation::Do(in1,out);
}

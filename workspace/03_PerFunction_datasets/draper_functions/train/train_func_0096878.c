isInSegmentEnvelopes(const Coordinate& intPt) const
{
	Envelope env0(*inputLines[0][0], *inputLines[0][1]);
	Envelope env1(*inputLines[1][0], *inputLines[1][1]);
	return env0.contains(intPt) && env1.contains(intPt);
}

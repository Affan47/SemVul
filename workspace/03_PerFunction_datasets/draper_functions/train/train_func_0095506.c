compareTo(const LineSegment& other) const
{
	int comp0=p0.compareTo(other.p0);
	if (comp0!=0) return comp0;
	return p1.compareTo(other.p1);
}

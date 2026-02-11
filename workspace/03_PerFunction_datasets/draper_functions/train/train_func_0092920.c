GetFaceVertexCount(size_t index) const
{
	size_t count = 0;
	if (index < GetFaceCount())
	{
		size_t holeCount = GetHoleCount(index);
		UInt32List::const_iterator it = faceVertexCounts.begin() + index + GetHoleCountBefore(index);
		UInt32List::const_iterator end = it + holeCount + 1;
		for (; it != end; ++it) count += (*it);
	}
	return count;
}

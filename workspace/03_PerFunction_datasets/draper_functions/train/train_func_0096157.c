calculateSerializeBufferSize() const
{
	unsigned baseSize = sizeof(btQuantizedBvh) + getAlignmentSerializationPadding();
	baseSize += sizeof(btBvhSubtreeInfo) * m_subtreeHeaderCount;
	if (m_useQuantization)
	{
		return baseSize + m_curNodeIndex * sizeof(btQuantizedBvhNode);
	}
	return baseSize + m_curNodeIndex * sizeof(btOptimizedBvhNode);
}

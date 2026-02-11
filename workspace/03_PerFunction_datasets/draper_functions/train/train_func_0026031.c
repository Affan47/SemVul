Clone(b2BlockAllocator* allocator) const
{
	void* mem = allocator->Allocate(sizeof(b2LoopShape));
	b2LoopShape* clone = new (mem) b2LoopShape;
	clone->Create(m_vertices, m_count);
	return clone;
}

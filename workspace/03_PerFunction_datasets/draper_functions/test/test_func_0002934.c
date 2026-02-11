plNewCompoundShape()
{
	void* mem = btAlignedAlloc(sizeof(btCompoundShape),16);
	return (plCollisionShapeHandle) new (mem)btCompoundShape();
}

compareTo(const Object *obj) const
{
	const IntSet *a = (const IntSet*)this;
	const IntSet *b = (const IntSet*)obj;
	if (a->mSetSize == b->mSetSize) {
		uint s = a->mSetSize ? idx2ByteOfs(a->mSetSize-1)+1 : 0;
		return memcmp(a->mSet, b->mSet, s);
	}
	return a->mSetSize - b->mSetSize;
}

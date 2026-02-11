findPrev(ObjHandle g) const
{
	if (!validHandle(g)) return findLast();
	SLinkedListNode *ng = handleToNative(g);
	if (ng == first) return invObjHandle;
	ObjHandle h = findFirst();
	while (h != invObjHandle) {
		SLinkedListNode *nh = handleToNative(h);
		if (nh->next == ng) return nativeToHandle(nh);
		h = findNext(h);
	}
	return invObjHandle;
}

set(ObjHandle h, Object *obj)
{
	DLinkedListNode *n = handleToNative(h);
	if (!n) return false;
	freeObj(n->obj);
	n->obj = obj;
	return true;
}

IoSeq_rawClone(IoSeq *proto)
{
	if (ISSYMBOL(proto))
	{
		return proto;
	}
	else
	{
		IoSeq *self = IoObject_rawClonePrimitive(proto);
		IoObject_setDataPointer_(self, UArray_clone(DATA(proto)));
		return self;
	}
}

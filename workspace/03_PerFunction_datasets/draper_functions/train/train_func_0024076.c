IoObject_objectProto(IoObject *self, IoObject *locals, IoMessage *m)
{


	IoObject *proto = IoObject_firstProto(self);
	return proto ? proto : IONIL(self);
}

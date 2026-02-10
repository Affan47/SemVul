IoObject_become(IoObject *self, IoObject *locals, IoMessage *m)
{
	IoObject *v = IoMessage_locals_valueArgAt_(m, locals, 0);

	if(self == v || IoObject_deref(v) == IoObject_deref(self)) return self;


	IOASSERT(ISOBJECT(self), "Primitives cannot become new values");

	IoObject_incrementMarkerCount(v);
	IoObject_dealloc(self);
	CollectorMarker_setObject_(self, IoObject_deref(v));
	return self;
}

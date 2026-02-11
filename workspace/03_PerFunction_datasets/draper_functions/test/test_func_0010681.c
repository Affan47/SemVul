IoObject_protoCompare(IoObject *self, IoObject *locals, IoMessage *m)
{


	IOASSERT(IoMessage_argCount(m), "compare requires argument");

	{
		IoSymbol *other = IoMessage_locals_valueArgAt_(m, locals, 0);
		return IONUMBER(IoObject_compare(self, other));
	}
}

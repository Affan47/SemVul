IoSeq_asBinaryNumber(IoSeq *self, IoObject *locals, IoMessage *m)
{


	IoNumber *byteCount = IoMessage_locals_valueArgAt_(m, locals, 0);
	size_t max = UArray_size(DATA(self));
	int bc = sizeof(double);
	double d = 0;

	if (!ISNIL(byteCount))
	{
		bc = IoNumber_asInt(byteCount);
	}

	if (max < bc)
	{
		IoState_error_(IOSTATE, m, "requested first %i bytes, but Sequence only contians %i bytes", bc, max);
	}

	memcpy(&d, UArray_bytes(DATA(self)), bc);
	return IONUMBER(d);
}

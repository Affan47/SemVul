IoSeq_atPut(IoSeq *self, IoObject *locals, IoMessage *m)
{


	size_t i = IoMessage_locals_longArgAt_(m, locals, 0);
	UArray *a = DATA(self);

	IO_ASSERT_NOT_SYMBOL(self);

	if (UArray_isFloatType(a))
	{
		double v = IoMessage_locals_doubleArgAt_(m, locals, 1);
		UArray_at_putDouble_(a, i, v);
	}
	else
	{
		long v = IoMessage_locals_longArgAt_(m, locals, 1);
		UArray_at_putLong_(a, i, v);
	}

	return self;
}

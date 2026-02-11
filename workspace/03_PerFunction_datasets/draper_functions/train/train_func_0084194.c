IoDuration_asString(IoDuration *self, IoObject *locals, IoMessage *m)
{


	UArray *ba;
	char *format = NULL;

	if (IoMessage_argCount(m) == 1)
	{
		format = CSTRING(IoMessage_locals_symbolArgAt_(m, locals, 0));
	}

	ba = Duration_asUArrayWithFormat_(DATA(self), format);
	return IoState_symbolWithUArray_copy_(IOSTATE, ba, 0);
}

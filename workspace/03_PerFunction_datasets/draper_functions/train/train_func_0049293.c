IoFile_assertOpen(IoFile *self, IoObject *locals, IoMessage *m)
{
	if (!DATA(self)->stream)
	{
		IoState_error_(IOSTATE, m, "file '%s' not yet open", CSTRING(DATA(self)->path));
	}
	return self;
}

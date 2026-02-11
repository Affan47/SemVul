IoFile_readUArrayOfLength_(IoFile *self, IoObject *locals, IoMessage *m)
{
	size_t length = IoMessage_locals_sizetArgAt_(m, locals, 0);
	UArray *ba = UArray_new();
	IoFile_assertOpen(self, locals, m);

	UArray_readNumberOfItems_fromCStream_(ba, length, DATA(self)->stream);

	if (ferror(DATA(self)->stream) != 0)
	{
		clearerr(DATA(self)->stream);
		UArray_free(ba);
		IoState_error_(IOSTATE, m, "error reading file '%s'", CSTRING(DATA(self)->path));
	}

	if (!UArray_size(ba))
	{
		UArray_free(ba);
		return NULL;
	}

	return ba;
}

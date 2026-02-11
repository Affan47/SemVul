IoNumber_asString(IoNumber *self, IoObject *locals, IoMessage *m)
{


	if (IoMessage_argCount(m) >= 1)
	{
		int whole = IoMessage_locals_intArgAt_(m, locals, 0);
		int part = 6;
		char *s;
		size_t length;
		IoObject *n;


		if (IoMessage_argCount(m) >= 2)
		{
			part = abs(IoMessage_locals_intArgAt_(m, locals, 1));
		}

		part  = abs(part);
		whole = abs(whole);


		length = 1024;
		s = io_calloc(1, length);

		snprintf(s, length, "%*.*f", whole, part, DATA(self));

		n = IOSEQ((unsigned char *)s, (size_t)strlen(s));

		io_free(s);

		return n;
	}

	return IoNumber_justAsString(self, locals, m);
}

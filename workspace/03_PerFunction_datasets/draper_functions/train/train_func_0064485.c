IoAsyncRequest_read(IoAsyncRequest *self, IoObject *locals, IoMessage *m)
{


	int r;

	IOCB(self)->aio_offset = (size_t)CNUMBER(IoMessage_locals_numberArgAt_(m, locals, 0));
	IOCB(self)->aio_nbytes = IoMessage_locals_intArgAt_(m, locals, 1);

	if (!IOCB_BUFFER(self))
	{
		IOCB(self)->aio_buf = calloc(1, IOCB(self)->aio_nbytes);
	}
	else
	{
		IOCB(self)->aio_buf = realloc(IOCB_BUFFER(self), IOCB(self)->aio_nbytes);
	}

	r = aio_read(IOCB(self));

	return r == 0 ? self : IONIL(self);
}

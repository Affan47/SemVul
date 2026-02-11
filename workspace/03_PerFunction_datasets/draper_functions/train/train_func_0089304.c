IoAsyncRequest_write(IoAsyncRequest *self, IoObject *locals, IoMessage *m)
{


	int r;
	IoSeq *data;
	UArray *ba;
	int bufferOffset;
	int bytesToWrite;

	IOCB(self)->aio_offset = (size_t)CNUMBER(IoMessage_locals_numberArgAt_(m, locals, 0));

	data = IoMessage_locals_seqArgAt_(m, locals, 1);
	ba = IoSeq_rawUArray(data);

	bufferOffset = IoMessage_locals_intArgAt_(m, locals, 2);
	bytesToWrite = IoMessage_locals_intArgAt_(m, locals, 3);

	if (bytesToWrite > UArray_size(ba) - bufferOffset)
	{
		bytesToWrite = UArray_size(ba) - bufferOffset;
	}

	IOCB(self)->aio_nbytes = bytesToWrite;
	IOCB(self)->aio_buf = realloc(IOCB_BUFFER(self), bytesToWrite);
	memcpy(IOCB_BUFFER(self), UArray_bytes(ba), bytesToWrite);

	r = aio_write(IOCB(self));

	return r == 0 ? self : IONIL(self);
}

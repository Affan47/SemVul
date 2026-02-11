IoOggStreamState_setSerialNumber(IoOggStreamState *self, IoObject *locals, IoMessage *m)
{


        int serial = IoMessage_locals_intArgAt_(m, locals, 0);
	int ret = ogg_stream_init(DATA(self), serial);
	IOASSERT(ret == 0, "ogg_stream_init returned non-zero value");

	return self;
}

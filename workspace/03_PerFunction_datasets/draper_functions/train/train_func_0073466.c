IoOggPage_bos(IoOggPage *self, IoObject *locals, IoMessage *m)
{


	int ret = ogg_page_bos(DATA(self));

	return ret ? IOTRUE(self) : IOFALSE(self);
}

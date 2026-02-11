IoMessage_free(IoMessage *self)
{
	IoMessageData *d = (IoMessageData *)IoObject_dataPointer(self);

	if (DATA(self)->args)
	{
		List_free(DATA(self)->args);
	}

	io_free(IoObject_dataPointer(self));
}

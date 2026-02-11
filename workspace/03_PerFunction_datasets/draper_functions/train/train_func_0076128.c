gsm0710_buffer_init(
	)
{
	GSM0710_Buffer* buf = (GSM0710_Buffer*)malloc(sizeof(GSM0710_Buffer));
	if (buf)
	{
		memset(buf, 0, sizeof(GSM0710_Buffer));
		buf->readp = buf->data;
		buf->writep = buf->data;
		buf->endp = buf->data + GSM0710_BUFFER_SIZE;
	}
	return buf;
}

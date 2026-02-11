CCURL_stream_read(GB_STREAM *stream, char *buffer, int len)
{
	void *_object = STREAM_TO_OBJECT(stream);
	int len_data;
	char *new_data;

	if ((THIS_STATUS != NET_RECEIVING_DATA ) && (THIS_STATUS != NET_INACTIVE)) return -1;

	len_data = GB.StringLength(THIS->data);

	if (len_data < len) return -1;

	memcpy(buffer, THIS->data, len);

	len_data -= len;

	if (len_data > 0)
		new_data = GB.NewString(THIS->data + len, len_data);
	else
		new_data = NULL;

	GB.FreeString(&THIS->data);
	THIS->data = new_data;

	return 0;
}

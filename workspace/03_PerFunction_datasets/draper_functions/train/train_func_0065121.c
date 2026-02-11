iks_stream_new (char *name_space, void *user_data, iksStreamHook *streamHook)
{
	ikstack *s;
	struct stream_data *data;

	s = iks_stack_new (DEFAULT_STREAM_CHUNK_SIZE, 0);
	if (NULL == s) return NULL;
	data = iks_stack_alloc (s, sizeof (struct stream_data));
	memset (data, 0, sizeof (struct stream_data));
	data->s = s;
	data->prs = iks_sax_extend (s, data, (iksTagHook *)tagHook, (iksCDataHook *)cdataHook, (iksDeleteHook *)deleteHook);
	data->name_space = name_space;
	data->user_data = user_data;
	data->streamHook = streamHook;
	return data->prs;
}

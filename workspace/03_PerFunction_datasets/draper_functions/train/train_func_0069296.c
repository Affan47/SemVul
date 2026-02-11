destroy_stream_list(io_Stream* stream_list, int* list_size)
{
	io_Stream* stream = get_last_stream(stream_list);
	while(stream->previous != NULL)
	{
		io_Stream* prev_stream = stream->previous;
		if(stream->indexes != NULL)
			g_free(stream->indexes);
		g_free(stream);
		stream = prev_stream;
		*list_size = *list_size - 1;
	}
	g_free(stream);
}

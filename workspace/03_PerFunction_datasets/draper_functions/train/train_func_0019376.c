SUBR_linput(void)
{
	STREAM *stream;
	char *addr;

	stream = get_stream(&SP[-1], TRUE);

	addr = STREAM_line_input(stream, NULL);

	SP--;
	if (!TYPE_is_integer(SP->type))
		RELEASE_OBJECT(SP);

	SP->type = T_STRING;
	SP->_string.addr = addr;
	SP->_string.start = 0;
	SP->_string.len = STRING_length(addr);

	SP++;
}

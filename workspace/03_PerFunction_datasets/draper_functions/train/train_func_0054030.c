isl_stream_push_char(__isl_keep isl_stream *s, int c)
{
	if (s->len >= s->size) {
		char *buffer;
		s->size = (3*s->size)/2;
		buffer = isl_realloc_array(s->ctx, s->buffer, char, s->size);
		if (!buffer)
			return -1;
		s->buffer = buffer;
	}
	s->buffer[s->len++] = c;
	return 0;
}

cafebabe_stream_read_uint8(struct cafebabe_stream *s, uint8_t *r)
{
	uint8_t *v = s->virtual;
	unsigned int i = s->virtual_i;

	if (i >= s->virtual_n) {
		s->cafebabe_errno = CAFEBABE_ERROR_UNEXPECTED_EOF;
		return 1;
	}

	*r = v[i];
	s->virtual_i += 1;
	return 0;
}

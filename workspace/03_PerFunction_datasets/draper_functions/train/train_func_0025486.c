stream_nextbit_n (ro_stream_t *s, unsigned int width)
{
	unsigned i;
	unsigned x;
	unsigned r = 0;
	for (i = 0; i < width; i++) {
		x = stream_nextbit (s);
		r |= (x << i);
	}
	return r;
}

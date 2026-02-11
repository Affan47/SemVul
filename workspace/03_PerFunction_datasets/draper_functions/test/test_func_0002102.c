utf8len(const char *s)
{
	static const int is_initial[] = {1, 1, 0, 1};

	size_t length = 0;
	for (; *s; ++s)
		length += is_initial[*s >> 6];

	return length;
}

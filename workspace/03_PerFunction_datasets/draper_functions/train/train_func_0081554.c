network_url_get_pathname(const struct network_url *url, char *buff, size_t size)
{
	const char *p;
	char *buff_end = buff + size;

	for (p = url->pathname; buff < buff_end; p++, buff++)
	{
		switch (*p)
		{
		case '\0':
		case '\r':
		case '\n':
		case '\f':
			*buff = 0;
			return buff;

		default:
			*buff = *p;
		}

	}

	return buff;
}

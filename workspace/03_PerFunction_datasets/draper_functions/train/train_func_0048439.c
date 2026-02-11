watch_find_callback(int fd)
{
	int i;

	for (i = 0; i < ARRAY_count(watch_callback); i++)
	{
		if (watch_callback[i].fd == fd)
			return i;
	}

	return -1;
}

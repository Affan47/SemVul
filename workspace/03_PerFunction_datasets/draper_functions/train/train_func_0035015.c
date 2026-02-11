exec_line_limit(int length)
{
	int limit = 0;

#ifdef ARG_MAX


	limit = ARG_MAX - 2048;


	if (limit > 20 * 1024)
		limit = 20 * 1024;


	limit -= length + 80;

	limit -= env_size();
#endif
#if !defined(ARG_MAX) && defined(_WIN32)


	limit = 2047 - length - 80;
#endif
	if (limit < 0)
		limit = 0;
	return limit;
}

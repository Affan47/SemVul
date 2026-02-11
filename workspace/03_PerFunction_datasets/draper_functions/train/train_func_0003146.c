sefs_query_set_range(sefs_query_t * query, const char *range, int match)
{
	if (query == NULL)
	{
		errno = EINVAL;
		return -1;
	}
	query->range(range, match);
	return 0;
}

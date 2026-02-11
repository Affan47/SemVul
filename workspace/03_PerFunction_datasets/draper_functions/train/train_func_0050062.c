cache_check_is_valid(struct cache_data *data,
				time_t current_time)
{
	if (data == NULL)
		return FALSE;

	if (data->cache_until < current_time)
		return FALSE;

	return TRUE;
}

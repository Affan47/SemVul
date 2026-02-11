upnp_count_mapping_kv(const void *key, void *u_value, void *data)
{
	const struct upnp_mapping *um = key;
	unsigned *count = data;

	(void) u_value;

	if (um->published)
		(*count)++;
}

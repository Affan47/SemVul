set_raw(const char *key, const void *data, uint size)
{
	return set_node(key, RNT_RAW, new ht_registry_data_raw(data, size));
}

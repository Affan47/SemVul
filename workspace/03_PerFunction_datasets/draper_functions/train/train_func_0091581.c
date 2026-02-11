test_map_remove(void *o, sha1_t *keys, size_t count)
{
	size_t i;
	map_t *m = o;

	for (i = 0; i < count; i++)
		map_remove(m, &keys[i]);
}

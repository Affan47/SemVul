sort_key_pairs(config_key_pair_t *key_a, config_key_pair_t *key_b)
{
	int size_a = strcmp(key_a->name, key_b->name);

	if (size_a < 0)
		return -1;
	else if (size_a > 0)
		return 1;

	return 0;
}

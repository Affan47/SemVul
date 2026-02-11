keyStat(Key *key)
{
	if (!key) return -1;

	key->flags |= KEY_FLAG_STAT;
	return 1;
}

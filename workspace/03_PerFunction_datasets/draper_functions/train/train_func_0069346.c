jdb_hash(const char* key)
{
	if (!key) {
		return 0;
	}
	unsigned int hash = 5381;
	unsigned int c;
	while ((c = *key++))
		hash = ((hash << 5) + hash) + (unsigned int)c;

	return (unsigned int) hash;
}

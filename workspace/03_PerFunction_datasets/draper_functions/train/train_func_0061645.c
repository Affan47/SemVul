hash(char symbol[])
{
	int hash = 0;
	int i = 0;
	while(symbol[i] != '\0')
	{
		hash += symbol[i];
		++i;
	}
	hash = hash % HASH_SIZE;
	return hash;
}

option_lookup(char letter, const option_t *ovec, int osize)
{
	int i;

	for (i = 0; i < osize; i++) {
		const option_t *entry = &ovec[i];

		g_assert(entry->letter);

		if (entry->letter[0] == letter)
			return entry;
	}

	return NULL;
}

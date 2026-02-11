keyword_hash(gconstpointer key)
{
	const gchar	*ptr;
	guint		hash = 0U, g;

	for(ptr = key; (*ptr != '\0') && (*ptr != '='); ptr++)
	{
		hash = (hash << 4) + *ptr;
		if((g = hash & 0xf0000000))
		{
			hash ^= (g >> 24);
			hash ^= g;
		}
	}
	return hash;
}

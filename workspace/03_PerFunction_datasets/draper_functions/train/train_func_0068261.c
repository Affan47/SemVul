g_istr_hash(gconstpointer v)
{
	const char *s = (const char *) v;
	unsigned int h = 0, g;

	while (*s != '\0') {
		h = (h << 4) + i_toupper(*s);
		if ((g = h & 0xf0000000UL)) {
			h = h ^ (g >> 24);
			h = h ^ g;
		}
		s++;
	}

	return h ;
}

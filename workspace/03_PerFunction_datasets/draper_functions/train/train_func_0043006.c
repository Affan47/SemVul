mhash(const char *cp, int mprime)
{

	unsigned	h = 0, g, at = 0;

	cp--;
	while (*++cp) {


		if (*cp == '(') {
			cp = skip_comment(&cp[1]) - 1;
			continue;
		}
		if (*cp == '"' || *cp == '\\')
			continue;
		if (*cp == '@')
			at++;
		h = ((h << 4) & 0xffffffff) + lowerconv(*cp & 0377);
		if ((g = h & 0xf0000000) != 0) {
			h = h ^ (g >> 24);
			h = h ^ g;
		}
	}
	return at ? h % mprime : mprime;
}

ynchecks(unsigned char *set, unsigned char *s)
{
	if (locale_map->type)
		return yncheck(set, utf8_decode_fwrd(&s, NULL));
	else
		return yncheck(set, s[0]);
}

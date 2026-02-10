get16_and_mask(char *from, uint16_t *to, uint16_t *mask, int base)
{
	char *p, *buffer;
	int i;

	if ( (p = strrchr(from, '/')) != NULL) {
		*p = '\0';
		i = strtol(p+1, &buffer, base);
		if (*buffer != '\0' || i < 0 || i > 65535)
			return -1;
		*mask = htons((uint16_t)i);
	} else
		*mask = 65535;
	i = strtol(from, &buffer, base);
	if (*buffer != '\0' || i < 0 || i > 65535)
		return -1;
	*to = htons((uint16_t)i);
	return 0;
}

print_ip(const char *prefix, uint32_t ip,
		     uint32_t mask, int invert)
{
	uint32_t bits, hmask = ntohl(mask);
	int i;

	if (!mask && !ip && !invert)
		return;

	printf("%s %s %u.%u.%u.%u",
		invert ? " !" : "",
		prefix,
		IP_PARTS(ip));

	if (mask == 0xFFFFFFFFU) {
		printf("/32");
		return;
	}

	i    = 32;
	bits = 0xFFFFFFFEU;
	while (--i >= 0 && hmask != bits)
		bits <<= 1;
	if (i >= 0)
		printf("/%u", i);
	else
		printf("/%u.%u.%u.%u", IP_PARTS(mask));
}

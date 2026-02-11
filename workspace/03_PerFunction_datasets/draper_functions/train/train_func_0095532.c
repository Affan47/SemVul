print_cookie(char *name, const uint8_t *cookie, int len)
{
	printf("  %s %02x%02x%02x%02x", name,
	       cookie[0], cookie[1],
	       cookie[2], cookie[3]);
	if (len == 8)
		printf("%02x%02x%02x%02x",
		       cookie[4], cookie[5],
		       cookie[6], cookie[7]);
}

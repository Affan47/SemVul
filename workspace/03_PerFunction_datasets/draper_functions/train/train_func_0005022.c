print_hex(void *p, int len)
{
	unsigned char *x = p;

	while (len--) {
		printf("%.2x", *x++);
		if (len)
			printf(":");
	}
}

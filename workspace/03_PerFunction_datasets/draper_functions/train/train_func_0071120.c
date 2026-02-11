print_lladdr(const u_int8_t *p, size_t l)
{
	const u_int8_t *ep, *q;

	q = p;
	ep = p + l;
	while (l > 0 && q < ep) {
		if (q > p)
			printf(":");
		printf("%02x", *q++);
		l--;
	}
}

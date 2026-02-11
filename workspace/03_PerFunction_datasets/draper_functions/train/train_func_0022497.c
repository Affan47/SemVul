output_records(int outfd)
{
	unsigned char zeroes[6] = {0, 0, 0, 0, 0, 0};
	struct ihex_binrec *p = records;

	while (p) {
		uint16_t writelen = (p->len + 9) & ~3;

		p->addr = htonl(p->addr);
		p->len = htons(p->len);
		if (write(outfd, &p->addr, writelen) != writelen)
			return 1;
		p = p->next;
	}


	if (write(outfd, zeroes, 6) != 6)
		return 1;
	return 0;
}

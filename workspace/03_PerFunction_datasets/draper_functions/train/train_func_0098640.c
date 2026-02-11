dump_gma(const char *name, const u8 *r)
{
	int i;

	printf("%12s address: ", name);
	for (i = 0; i < 3; i++) {
		u16 a = *(u16 *)(r + i * 4);
		printf(" %02X %02X", a & 0xff, (a >> 8) & 0xff);
	}
	printf("\n");
}

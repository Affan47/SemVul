dump_prefetch(const char *name, const void *r)
{
	const u32 *reg = r;

	printf("\n%s Prefetch\n", name);
	printf("Control               0x%08X\n", reg[0]);
	printf("Last Index            %u\n", reg[1]);
	printf("Start Address         0x%08x%08x\n", reg[3], reg[2]);
	if (*name == 'S') {
		printf("TX1 report            %u\n", reg[4]);
		printf("TX2 report            %u\n", reg[5]);
		printf("TX threshold          %u\n", reg[6]);
		printf("Put Index             %u\n", reg[7]);
	} else {
		printf("Get Index             %u\n", reg[4]);
		printf("Put Index             %u\n", reg[5]);
	}
}

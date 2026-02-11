decode_cache(struct cpudata *cpu, struct _cache_table *table, int output)
{
	int i, j, n;
	long regs[4];
	unsigned char *dp = (unsigned char *)regs;


	cpuid (cpu->number, 2, &regs[0], &regs[1], &regs[2], &regs[3]);


	n = regs[0] & 0xff;

	for (i=0 ; i<n ; i++) {
		cpuid(cpu->number, 2, &regs[0], &regs[1], &regs[2], &regs[3]);


		for (j=0; j<3; j++)
			if (regs[j] < 0)
				regs[j] = 0;


		for (j=1; j<16; j++)
			if (dp[j]!=0)
				decode_Intel_cache (dp[j], cpu, output, table);
	}
}

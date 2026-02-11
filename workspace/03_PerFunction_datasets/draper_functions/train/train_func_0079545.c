osummary(void)
{

	int i, *p;

	if(foutput == 0)
		return;
	i = 0;
	for(p = maxa; p >= amem; p--)
		if(*p == 0)
			i++;

	Bprint(foutput, "Optimizer space used: input %d/%d, output %d/%d\n",
		(int)(pmem-mem0+1), MEMSIZE, (int)(maxa-amem+1), ACTSIZE);
	Bprint(foutput, "%d table entries, %d zero\n", (int)(maxa-amem+1), i);
	Bprint(foutput, "maximum spread: %d, maximum offset: %d\n", maxspr, maxoff);
}

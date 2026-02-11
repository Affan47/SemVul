read_msr(int cpu, unsigned int idx, unsigned long long *val)
{
	char cpuname[16];
	unsigned char buffer[8];
	unsigned long lo, hi;
	int fh;
	static int nodriver=0;

	if (nodriver==1)
		return 0;

	sprintf (cpuname, "/dev/cpu/%d/msr", cpu);

	fh = open (cpuname, O_RDONLY);
	if (fh==-1) {
		if (!silent)
			perror(cpuname);
		nodriver=1;
		return (0);
	}

	lseek (fh, idx, SEEK_CUR);

	if (fh != -1) {

		if (read (fh, &buffer[0], 8) != 8) {
			close (fh);
			return (0);
		}

		lo = (*(unsigned long *)buffer);
		hi = (*(unsigned long *)(buffer+4));
		*val = hi;
		*val = (*val<<32) | lo;
	}
	close (fh);
	return (1);
}

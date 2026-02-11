e2p_mntopt2string(unsigned int mask)
{
	struct mntopt  *f;
	static char buf[20];
	int	fnum;

	for (f = mntopt_list; f->string; f++) {
		if (mask == f->mask)
			return f->string;
	}
	for (fnum = 0; mask >>= 1; fnum++);
	sprintf(buf, "MNTOPT_%d", fnum);
	return buf;
}

parse_stats(unsigned counters[STATS_END], char *buf)
{
	int i;
	char *p, *p2;

	p = buf;
	for (i=0;i<STATS_END;i++) {
		counters[i] += strtol(p, &p2, 10);
		if (!p2 || p2 == p) break;
		p = p2;
	}
}

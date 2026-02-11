printproto(struct protox *tp, const char *name)
{
	void (*pr)(const char *);

	if (sflag) {
		pr = tp->pr_stats;
	} else {
		pr = tp->pr_cblocks;
	}
	if (pr != NULL)
		(*pr)(name);
}

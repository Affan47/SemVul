maybe_leb_gced(struct ubifs_info *c, int lnum, int gc_seq1)
{
	int gc_seq2, gced_lnum;

	gced_lnum = c->gced_lnum;
	smp_rmb();
	gc_seq2 = c->gc_seq;

	if (gc_seq1 == gc_seq2)
		return 0;

	if (gc_seq1 + 1 != gc_seq2)
		return 1;


	smp_rmb();
	if (gced_lnum != c->gced_lnum)
		return 1;

	if (gced_lnum == lnum)
		return 1;
	return 0;
}

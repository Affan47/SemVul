est_seqQ(const bcf_callaux_t *bca, int l, int l_run)
{
	int q, qh;
	q = bca->openQ + bca->extQ * (abs(l) - 1);
	qh = l_run >= 3? (int)(bca->tandemQ * (double)abs(l) / l_run + .499) : 1000;
	return q < qh? q : qh;
}

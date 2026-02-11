merge_bs(struct bs **bsap, unsigned int *nr_bsap,
		     struct bs *bsb, unsigned int nr_bsb)
{
	struct bs *bsa = *bsap;
	unsigned int nr_bsa = *nr_bsap;
	int a, b;

	for (b = 0; b < nr_bsb; b++) {
		int next, found = 0;

		for (a = 0; a < nr_bsa; a++) {
			if (bsb[b].bs != bsa[a].bs)
				continue;

			bsa[a].nr += bsb[b].nr;
			bsa[a].merges += bsb[b].merges;
			found = 1;
			break;
		}

		if (found)
			continue;

		next = *nr_bsap;
		bsa = realloc(bsa, (next + 1) * sizeof(struct bs));
		bsa[next].bs = bsb[b].bs;
		bsa[next].nr = bsb[b].nr;
		(*nr_bsap)++;
		*bsap = bsa;
	}
}

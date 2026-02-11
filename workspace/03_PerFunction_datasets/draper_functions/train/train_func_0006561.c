swap_inequality(struct isl_basic_map *bmap, int a, int b)
{
	if (a != b) {
		isl_int *t = bmap->ineq[a];
		bmap->ineq[a] = bmap->ineq[b];
		bmap->ineq[b] = t;
	}
}

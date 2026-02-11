reduced_using_equalities(isl_int *dst, isl_int *src,
	struct isl_basic_map *bmap, int *elim)
{
	int d;
	int copied = 0;
	unsigned total;

	total = isl_space_dim(bmap->dim, isl_dim_all);
	for (d = total - 1; d >= 0; --d) {
		if (isl_int_is_zero(src[1+d]))
			continue;
		if (elim[d] == -1)
			continue;
		if (!copied) {
			isl_seq_cpy(dst, src, 1 + total);
			copied = 1;
		}
		isl_seq_elim(dst, bmap->eq[elim[d]], 1 + d, 1 + total, NULL);
	}
	return copied;
}

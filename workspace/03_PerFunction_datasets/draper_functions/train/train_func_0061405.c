rkd_tree(
	ANNpointArray		pa,
	ANNidxArray			pidx,
	int					n,
	int					dim,
	int					bsp,
	ANNorthRect			&bnd_box,
	ANNkd_splitter		splitter)
{
	if (n <= bsp) {
		if (n == 0)
			return KD_TRIVIAL;
		else
			return new ANNkd_leaf(n, pidx);
	}
	else {
		int cd;
		ANNcoord cv;
		int n_lo;
		ANNkd_node *lo, *hi;


		(*splitter)(pa, pidx, bnd_box, n, dim, cd, cv, n_lo);

		ANNcoord lv = bnd_box.lo[cd];
		ANNcoord hv = bnd_box.hi[cd];

		bnd_box.hi[cd] = cv;
		lo = rkd_tree(
				pa, pidx, n_lo,
				dim, bsp, bnd_box, splitter);
		bnd_box.hi[cd] = hv;

		bnd_box.lo[cd] = cv;
		hi = rkd_tree(
				pa, pidx + n_lo, n-n_lo,
				dim, bsp, bnd_box, splitter);
		bnd_box.lo[cd] = lv;


		ANNkd_split *ptr = new ANNkd_split(cd, cv, lv, hv, lo, hi);

		return ptr;
	}
}

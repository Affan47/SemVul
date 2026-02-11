fair_split(
	ANNpointArray		pa,
	ANNidxArray			pidx,
	const ANNorthRect	&bnds,
	int					n,
	int					dim,
	int					&cut_dim,
	ANNcoord			&cut_val,
	int					&n_lo)
{
	int d;
	ANNcoord max_length = bnds.hi[0] - bnds.lo[0];
	cut_dim = 0;
	for (d = 1; d < dim; d++) {
		ANNcoord length = bnds.hi[d] - bnds.lo[d];
		if (length > max_length) {
			max_length = length;
			cut_dim = d;
		}
	}

	ANNcoord max_spread = 0;
	cut_dim = 0;
	for (d = 0; d < dim; d++) {
		ANNcoord length = bnds.hi[d] - bnds.lo[d];


		if (((double) max_length)*2.0/((double) length) <= FS_ASPECT_RATIO) {

			ANNcoord spr = annSpread(pa, pidx, n, d);
			if (spr > max_spread) {
				max_spread = spr;
				cut_dim = d;
			}
		}
	}

	max_length = 0;
	for (d = 0; d < dim; d++) {
		ANNcoord length = bnds.hi[d] - bnds.lo[d];
		if (d != cut_dim && length > max_length)
			max_length = length;
	}

	ANNcoord small_piece = max_length / FS_ASPECT_RATIO;
	ANNcoord lo_cut = bnds.lo[cut_dim] + small_piece;
	ANNcoord hi_cut = bnds.hi[cut_dim] - small_piece;

	int br1, br2;

	if (annSplitBalance(pa, pidx, n, cut_dim, lo_cut) >= 0) {
		cut_val = lo_cut;
		annPlaneSplit(pa, pidx, n, cut_dim, cut_val, br1, br2);
		n_lo = br1;
	}

	else if (annSplitBalance(pa, pidx, n, cut_dim, hi_cut) <= 0) {
		cut_val = hi_cut;
		annPlaneSplit(pa, pidx, n, cut_dim, cut_val, br1, br2);
		n_lo = br2;
	}
	else {
		n_lo = n/2;
		annMedianSplit(pa, pidx, n, cut_dim, cut_val, n_lo);
	}
}

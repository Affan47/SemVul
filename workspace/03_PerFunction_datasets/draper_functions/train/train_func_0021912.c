annEnclRect(
	ANNpointArray		pa,
	ANNidxArray			pidx,
	int					n,
	int					dim,
	ANNorthRect			&bnds)
{
	for (int d = 0; d < dim; d++) {
		ANNcoord lo_bnd = PA(0,d);
		ANNcoord hi_bnd = PA(0,d);
		for (int i = 0; i < n; i++) {
			if (PA(i,d) < lo_bnd) lo_bnd = PA(i,d);
			else if (PA(i,d) > hi_bnd) hi_bnd = PA(i,d);
		}
		bnds.lo[d] = lo_bnd;
		bnds.hi[d] = hi_bnd;
	}
}

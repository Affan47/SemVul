selectDecomp(
	ANNpointArray		pa,
	ANNidxArray			pidx,
	int					n,
	int					dim,
	const ANNorthRect	&bnd_box,
	ANNkd_splitter		splitter,
	ANNshrinkRule		shrink,
	ANNorthRect			&inner_box)
{
	ANNdecomp decomp = SPLIT;

	switch (shrink) {
	case ANN_BD_NONE:
		decomp = SPLIT;
		break;
	case ANN_BD_SUGGEST:
	case ANN_BD_SIMPLE:
		decomp = trySimpleShrink(
				pa, pidx,
				n, dim,
				bnd_box,
				inner_box);
		break;
	case ANN_BD_CENTROID:
		decomp = tryCentroidShrink(
				pa, pidx,
				n, dim,
				bnd_box,
				splitter,
				inner_box);
		break;
	default:
		annError("Illegal shrinking rule", ANNabort);
	}
	return decomp;
}

annkSearch(
	ANNpoint			q,
	int					k,
	ANNidxArray			nn_idx,
	ANNdistArray		dd,
	double				eps)
{
	ANNmin_k mk(k);
	int i;

	if (k > n_pts) {
		annError("Requesting more near neighbors than data points", ANNabort);
	}

	for (i = 0; i < n_pts; i++) {

		ANNdist sqDist = annDist(dim, pts[i], q);
		if (ANN_ALLOW_SELF_MATCH || sqDist != 0)
			mk.insert(sqDist, i);
	}
	for (i = 0; i < k; i++) {
		dd[i] = mk.ith_smallest_key(i);
		nn_idx[i] = mk.ith_smallest_info(i);
	}
}

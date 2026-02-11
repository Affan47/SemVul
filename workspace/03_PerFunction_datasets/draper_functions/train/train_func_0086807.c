ann_pri_search(ANNdist box_dist)
{
	ANNdist new_dist;

	ANNcoord cut_diff = ANNprQ[cut_dim] - cut_val;

	if (cut_diff < 0) {
		ANNcoord box_diff = cd_bnds[ANN_LO] - ANNprQ[cut_dim];
		if (box_diff < 0)
			box_diff = 0;

		new_dist = (ANNdist) ANN_SUM(box_dist,
				ANN_DIFF(ANN_POW(box_diff), ANN_POW(cut_diff)));

		if (child[ANN_HI] != KD_TRIVIAL)
			ANNprBoxPQ->insert(new_dist, child[ANN_HI]);

		child[ANN_LO]->ann_pri_search(box_dist);
	}
	else {
		ANNcoord box_diff = ANNprQ[cut_dim] - cd_bnds[ANN_HI];
		if (box_diff < 0)
			box_diff = 0;

		new_dist = (ANNdist) ANN_SUM(box_dist,
				ANN_DIFF(ANN_POW(box_diff), ANN_POW(cut_diff)));

		if (child[ANN_LO] != KD_TRIVIAL)
			ANNprBoxPQ->insert(new_dist, child[ANN_LO]);

		child[ANN_HI]->ann_pri_search(box_dist);
	}
	ANN_SPL(1)
	ANN_FLOP(8)
}

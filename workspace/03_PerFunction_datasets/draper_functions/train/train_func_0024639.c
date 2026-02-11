ann_search(ANNdist box_dist)
{

	if (ANNmaxPtsVisited != 0 && ANNptsVisited > ANNmaxPtsVisited) return;

	ANNdist inner_dist = 0;
	for (int i = 0; i < n_bnds; i++) {
		if (bnds[i].out(ANNkdQ)) {

			inner_dist = (ANNdist) ANN_SUM(inner_dist, bnds[i].dist(ANNkdQ));
		}
	}
	if (inner_dist <= box_dist) {
		child[ANN_IN]->ann_search(inner_dist);
		child[ANN_OUT]->ann_search(box_dist);
	}
	else {
		child[ANN_OUT]->ann_search(box_dist);
		child[ANN_IN]->ann_search(inner_dist);
	}
	ANN_FLOP(3*n_bnds)
	ANN_SHR(1)
}

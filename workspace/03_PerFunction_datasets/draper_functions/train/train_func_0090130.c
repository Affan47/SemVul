kdtree_compute_levels(int N, int Nleaf) {
	int nnodes = N / Nleaf;
	int maxlevel = 1;
	while (nnodes) {
		nnodes = nnodes >> 1;
		maxlevel++;
	}
	return maxlevel;
}

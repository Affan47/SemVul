Lattice (int n, int m)
{
	Graph *g;
	Edge *e;
	int i, j;

	g = grid (n, m);


	for (j = 0; j < n; ++j) {
		for (i = 1; i < m; ++i) {
			e = new Edge ((*g)[j * m + i - 1], (*g)[j * m + i]);
			g->add (e);
		}
	}


	for (i = 0; i < m; ++i) {
		for (j = 0; j < (n - 1); ++j) {
			e = new Edge ((*g)[i + m * j], (*g)[i + m * (j+1)]);
			g->add (e);
		}
	}

	return g;
}

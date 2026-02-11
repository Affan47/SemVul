K (int n, int m)
{
	Graph *g;
	Vertex *v;
	int i, j, sx, sy, x;

	g = new Graph ();


	sy = height / 3;

	sx = width / (n + 1);
	for (x = 0; x < n; ++x) {
		v = new Vertex ("", (x + 1) * sx, sy);
		g->add (v);
	}
	sx = width / (m + 1);
	for (x = 0; x < m; ++x) {
		v = new Vertex ("", (x + 1) * sx, 2 * sy);
		g->add (v);
	}


	for (i = 0; i < n; ++i) {
		for (j = 0; j < m; ++j)
			g->add (new Edge ((*g)[i], (*g)[n + j]));
	}

	return g;
}

adjacency_matrix () const
{
	Matrix ret (order (), order ());
	unsigned int i, j;

	for (j = 0; j < order (); ++j)
		for (i = 0; i < order (); ++i) {
			if (i == j) {
				ret (i, j) = 0;
				continue;
			}
			Edge *e = find (V[i], V[j], true);
			if (!e) {
				e = find (V[i], V[j], false);
				if (e && e->directed && (e->v == V[j]))
					e = NULL;
			}
			ret (i, j) = e ? e->weight : 0;
		}

	return ret;
}

sp_symetree(
	    int *acolst, int *acolend,
	    int *arow,
	    int n,
	    int *parent
	    )
{
	int	*root;
	int	rset, cset;
	int	row, col;
	int	rroot;
	int	p;

	root = mxCallocInt (n);
	initialize_disjoint_sets (n);

	for (col = 0; col < n; col++) {
		cset = make_set (col);
		root[cset] = col;
		parent[col] = n;
		for (p = acolst[col]; p < acolend[col]; p++) {
			row = arow[p];
			if (row >= col) continue;
			rset = find (row);
			rroot = root[rset];
			if (rroot != col) {
				parent[rroot] = col;
				cset = link (cset, rset);
				root[cset] = col;
			}
		}
	}
	SUPERLU_FREE (root);
	finalize_disjoint_sets ();
	return 0;
}

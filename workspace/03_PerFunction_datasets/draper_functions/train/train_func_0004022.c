initLayout(vtx_data * graph, int n, int dim, double **coords,
	   node_t ** nodes)
{
    node_t *np;
    double *xp;
    double *yp;
    double *pt;
    int i, d;
    int pinned = 0;

    xp = coords[0];
    yp = coords[1];
    for (i = 0; i < n; i++) {
	np = nodes[i];
	if (hasPos(np)) {
	    pt = ND_pos(np);
	    *xp++ = *pt++;
	    *yp++ = *pt++;
	    if (dim > 2) {
		for (d = 2; d < dim; d++)
		    coords[d][i] = *pt++;
	    }
	    if (isFixed(np))
		pinned = 1;
	} else {
	    *xp++ = drand48();
	    *yp++ = drand48();
	    if (dim > 2) {
		for (d = 2; d < dim; d++)
		    coords[d][i] = drand48();
	    }
	}
    }

    for (d = 0; d < dim; d++)
	orthog1(n, coords[d]);

    return pinned;
}

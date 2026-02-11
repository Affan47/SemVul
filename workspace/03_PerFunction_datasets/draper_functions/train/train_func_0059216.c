initialPositions(graph_t * g)
{
    int i;
    node_t *np;
    attrsym_t *possym;
    attrsym_t *pinsym;
    double *pvec;
    char *p;
    char c;

    possym = agattr(g,AGNODE, "pos", NULL);
    if (!possym)
	return;
    pinsym = agattr(g,AGNODE, "pin", NULL);
    for (i = 0; (np = GD_neato_nlist(g)[i]); i++) {
	p = agxget(np, possym);
	if (p[0]) {
	    pvec = ND_pos(np);
	    c = '\0';
	    if (sscanf(p, "%lf,%lf%c", pvec, pvec + 1, &c) >= 2) {
		if (PSinputscale > 0.0) {
		    int i;
		    for (i = 0; i < NDIM; i++)
			pvec[i] = pvec[i] / PSinputscale;
		}
		ND_pinned(np) = P_SET;
		if ((c == '!')
		    || (pinsym && mapbool(agxget(np, pinsym))))
		    ND_pinned(np) = P_PIN;
	    } else
		fprintf(stderr,
			"Warning: node %s, position %s, expected two floats\n",
			agnameof(np), p);
	}
    }
}

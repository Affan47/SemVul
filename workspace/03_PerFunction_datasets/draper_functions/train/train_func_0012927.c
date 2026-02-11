getRankseps (Agraph_t* g, int maxrank)
{
    char *p;
    char *endp;
    char c;
    int i, rk = 1;
    double* ranks = N_NEW(maxrank+1, double);
    double xf = 0, delx, d;

    if ((p = late_string(g, agfindgraphattr(g->root, "ranksep"), NULL))) {
	while ((rk <= maxrank) && ((d = strtod (p, &endp)) > 0)) {
	    delx = MAX(d, MIN_RANKSEP);
	    xf += delx;
	    ranks[rk++] = xf;
	    p = endp;
	    while ((c = *p) && (isspace(c) || (c == ':')))
		p++;
	}
    }
    else {
	delx = DEF_RANKSEP;
    }

    for (i = rk; i <= maxrank; i++) {
	xf += delx;
	ranks[i] = xf;
    }

    return ranks;
}

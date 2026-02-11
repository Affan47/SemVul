doRep(node_t * p, node_t * q, double xdelta, double ydelta, double dist2)
{
    int ov;
    double force;

#if defined(DEBUG) || defined(MS) || defined(ALT)
    double dist;
#endif


    while (dist2 == 0.0) {
	xdelta = 5 - rand() % 10;
	ydelta = 5 - rand() % 10;
	dist2 = xdelta * xdelta + ydelta * ydelta;
    }
#if defined(MS)
    dout = boxDist(p, q);
    if (dout < EPSILON)
	dout = EPSILON;
    dist = sqrt(dist2);
    force = K2 / (dout * dist);
#elif defined(ALT)
    force = K2 / dist2;
    dist = sqrt(dist2);
    din = RAD(p) + RAD(q);
    if (ov = overlap(p, q)) {
	factor = X_C;
    } else {
	ov = 0;
	if (dist <= din + X_K)
	    factor = X_C * (X_K - (dist - din)) / X_K;
	else
	    factor = 0.0;
    }
    force *= factor;
#elif defined(ORIG)
    force = K2 / dist2;
    if ((ov = overlap(p, q)))
	force *= X_C;
#else
    if ((ov = overlap(p, q)))
	force = X_ov / dist2;
    else
	force = X_nonov / dist2;
#endif
#ifdef DEBUG
    if (Verbose == 4) {
	prIndent();
	dist = sqrt(dist2);
	fprintf(stderr, " ov Fr %f dist %f\n", force * dist, dist);
    }
#endif
    DISP(q)[0] += xdelta * force;
    DISP(q)[1] += ydelta * force;
    DISP(p)[0] -= xdelta * force;
    DISP(p)[1] -= ydelta * force;
    return ov;
}

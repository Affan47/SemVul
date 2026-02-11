mkCtrlPts(int s, int mult, pointf prev, pointf v,
			   pointf nxt, tripoly_t * trip)
{
    pointf *ps;
    int idx = ctrlPtIdx(v, &(trip->poly));
    int i;
    double d, sep, theta, sinTheta, cosTheta;
    pointf q, w;

    if (idx < 0)
	return NULL;

    ps = N_GNEW(mult, pointf);
    theta = bisect(prev, v, nxt);
    sinTheta = sin(theta);
    cosTheta = cos(theta);
    w.x = v.x + 100 * cosTheta;
    w.y = v.y + 100 * sinTheta;
    if (idx > s) {
	if (wind(prev, v, w) != 1) {
	    sinTheta *= -1;
	    cosTheta *= -1;
	    w.x = v.x + 100 * cosTheta;
	    w.y = v.y + 100 * sinTheta;
	}
    } else if (wind(prev, v, w) != -1) {
	sinTheta *= -1;
	cosTheta *= -1;
	w.x = v.x + 100 * cosTheta;
	w.y = v.y + 100 * sinTheta;
    }

    if (triPoint(trip, idx, v, w, &q)) {
	return 0;
    }

    d = DIST(q, v);
    if (d >= mult * SEP)
	sep = SEP;
    else
	sep = d / mult;
    if (idx < s) {
	for (i = 0; i < mult; i++) {
	    ps[i].x = v.x + i * sep * cosTheta;
	    ps[i].y = v.y + i * sep * sinTheta;
	}
    } else {
	for (i = 0; i < mult; i++) {
	    ps[mult - i - 1].x = v.x + i * sep * cosTheta;
	    ps[mult - i - 1].y = v.y + i * sep * sinTheta;
	}
    }
    return ps;
}

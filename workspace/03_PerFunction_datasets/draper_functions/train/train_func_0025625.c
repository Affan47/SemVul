icmLut_min_max(
	icmLut *p,
	double *minp,
	double *maxp,
	int chan
) {
	double *tp;
	double minv, maxv;
	unsigned int e, ee, f;
	int gc[MAX_CHAN];

	minv = 1e6;
	maxv = -1e6;

	for (e = 0; e < p->inputChan; e++)
		gc[e] = 0;


	for (tp = p->clutTable, e = 0; e < p->inputChan; tp += p->outputChan) {
		double v;
		if (chan == -1) {
			for (v = 0.0, f = 0; f < p->outputChan; f++)
				v += tp[f];
		} else {
			v = tp[chan];
		}
		if (v < minv) {
			minv = v;
			for (ee = 0; ee < p->inputChan; ee++)
				minp[ee] = gc[ee]/(p->clutPoints-1.0);
		}
		if (v > maxv) {
			maxv = v;
			for (ee = 0; ee < p->inputChan; ee++)
				maxp[ee] = gc[ee]/(p->clutPoints-1.0);
		}


		for (e = 0; e < p->inputChan; e++) {
			if (++gc[e] < p->clutPoints)
				break;
			gc[e] = 0;
		}
	}
}

contest(nnq, al,b,g,r)
nn_quant *nnq;
register int al,b,g,r;
{


	register int i,dist,a,biasdist,betafreq;
	int bestpos,bestbiaspos,bestd,bestbiasd;
	register int *p,*f, *n;

	bestd = ~(((int) 1)<<31);
	bestbiasd = bestd;
	bestpos = -1;
	bestbiaspos = bestpos;
	p = nnq->bias;
	f = nnq->freq;

	for (i=0; i< nnq->netsize; i++) {
		n = nnq->network[i];
		dist = n[0] - al;
		if (dist<0) dist = -dist;
		a = n[1] - b;
		if (a<0) a = -a;
		dist += a;
		a = n[2] - g;
		if (a<0) a = -a;
		dist += a;
		a = n[3] - r;
		if (a<0) a = -a;
		dist += a;
		if (dist<bestd) {
			bestd=dist;
			bestpos=i;
		}
		biasdist = dist - ((*p)>>(intbiasshift-netbiasshift));
		if (biasdist<bestbiasd) {
			bestbiasd=biasdist;
			bestbiaspos=i;
		}
		betafreq = (*f >> betashift);
		*f++ -= betafreq;
		*p++ += (betafreq<<gammashift);
	}
	nnq->freq[bestpos] += beta;
	nnq->bias[bestpos] -= betagamma;
	return(bestbiaspos);
}

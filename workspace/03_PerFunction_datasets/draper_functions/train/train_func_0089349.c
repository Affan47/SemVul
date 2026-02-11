contest(ILint b, ILint g, ILint r)
{


	ILint i,dist,a,biasdist,betafreq;
	ILint bestpos,bestbiaspos,bestd,bestbiasd;
	ILint *p,*f, *n;

	bestd = ~(((ILint) 1)<<31);
	bestbiasd = bestd;
	bestpos = -1;
	bestbiaspos = bestpos;
	p = bias;
	f = freq;

	for (i=0; i<netsizethink; i++) {
		n = network[i];
		dist = n[0] - b;   if (dist<0) dist = -dist;
		a = n[1] - g;   if (a<0) a = -a;
		dist += a;
		a = n[2] - r;   if (a<0) a = -a;
		dist += a;
		if (dist<bestd) {bestd=dist; bestpos=i;}
		biasdist = dist - ((*p)>>(intbiasshift-netbiasshift));
		if (biasdist<bestbiasd) {bestbiasd=biasdist; bestbiaspos=i;}
		betafreq = (*f >> betashift);
		*f++ -= betafreq;
		*p++ += (betafreq<<gammashift);
	}
	freq[bestpos] += beta;
	bias[bestpos] -= betagamma;
	return(bestbiaspos);
}

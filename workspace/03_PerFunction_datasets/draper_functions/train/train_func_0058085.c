sectorBounds(unsigned int s, float& r0, float& r1, float& ph0, float& ph1) const {
	if(s>=nSectors()) {
		r0=r1=r;
		ph0=0;
		ph1=6.28318531;
		return;
	}
	unsigned int rng = getRing(s);
	r0 = rng>0?ringRadius(rng-1):0;
	r1 = ringRadius(rng);
	s -= cumdivs[rng];
	ph0 = 2*M_PI*float(s)/float(ndivs[rng]);
	ph1 = 2*M_PI*float(s+1)/float(ndivs[rng]);
}

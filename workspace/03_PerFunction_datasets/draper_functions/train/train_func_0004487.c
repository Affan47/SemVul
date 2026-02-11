rle_compute_triangle_count(unsigned int count, unsigned int nrepcodes)
{
	unsigned int perrep;
	unsigned int cost;

	cost = 0;
	perrep = (nrepcodes * (nrepcodes+1)) / 2;
	while (count >= perrep){
		cost += nrepcodes;
		count -= perrep;
	}
	if (count > 0){
		unsigned int n;
		n = rle_isqrt(count);
		while ((n*(n+1)) >= 2*count) n --;
		while ((n*(n+1)) < 2*count) n ++;
		cost += n;
	}
	return(cost);
}

merge(int lo, int ls, int rs, int p[], real_t a[], int hp[])
{


	int l,r,lout,rout,i,pl,pr;

	l=lo;
	r=lo+ls;
	lout=rout=0;
	i=lo;
	do {
		pl=p[l];
		pr=p[r];
		if (a[pl] > a[pr]) {
			hp[i]=pr;
			r++;
			rout = (r == lo+ls+rs);
		} else {
			hp[i]=pl;
			l++;
			lout = (l == lo+ls);
		}
		i++;
	} while (!(lout || rout));
	if (rout) {
		for (i=lo+ls-1; i>=l; i--) p[i+rs]=p[i];
		r=l+rs;
	}
	for (i=r-1; i>=lo; i--) p[i]=hp[i];
}

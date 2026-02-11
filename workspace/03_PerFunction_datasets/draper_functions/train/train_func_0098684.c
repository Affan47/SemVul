annPlaneSplit(
	ANNpointArray		pa,
	ANNidxArray			pidx,
	int					n,
	int					d,
	ANNcoord			cv,
	int					&br1,
	int					&br2)
{
	int l = 0;
	int r = n-1;
	for(;;) {
		while (l < n && PA(l,d) < cv) l++;
		while (r >= 0 && PA(r,d) >= cv) r--;
		if (l > r) break;
		PASWAP(l,r);
		l++; r--;
	}
	br1 = l;
	r = n-1;
	for(;;) {
		while (l < n && PA(l,d) <= cv) l++;
		while (r >= br1 && PA(r,d) > cv) r--;
		if (l > r) break;
		PASWAP(l,r);
		l++; r--;
	}
	br2 = l;
}

asum( int n, int c[], Point Q[])
{
	int        maxd = 0;
	int        cs = 0;
	Point      P;

	for (int i=0; i<n; i++) {
		cs += c[i];
		if (Q[i].dim() > maxd)
			maxd = Q[i].dim();
	}
	if (cs != 1)
		P.err = Esum;

	for (int i=0; i<n; i++) {
		P.x += c[i] * Q[i].x;
		P.y += c[i] * Q[i].y;
		P.z += c[i] * Q[i].z;
	}
	P.dimn = maxd;
	return P;
}

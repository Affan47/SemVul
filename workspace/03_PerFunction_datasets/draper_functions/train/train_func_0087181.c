solve(const double *b, bool &worked) const {
	if (m!=n) {
		cerr << "invalid cmatrix in solve" << endl;
		exit(1);
	}
	double *ret = new double[n];
	for(int i=0;i<n;i++) ret[i] = b[i];
	int *ix = new int[n];
	cmatrix a(n,n);

	if (!LUdecomp(a,ix)) {
		worked = false;
		delete []ix;
		return ret;
	}
	worked=true;
	a.LUbacksub(ix,ret);
	delete []ix;
	return ret;
}

rw(void) {
	int i, j;

	for(i=0;i<N(r);i++) {

		r[i].br=0;
		Z(&r[i].i);
		for(j=0;j<N(r->ri);j++) {
			r[i].i[j]=r[i].ri[j];
		}

		r[i].e=r[i].re;
		r[i].s=r[i].rs;
	}
}

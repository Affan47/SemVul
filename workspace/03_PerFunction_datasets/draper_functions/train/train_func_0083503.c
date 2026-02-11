praxisflin(real_t l, int j, int n, real_t x[], real_t **v,
			real_t *qa, real_t *qb, real_t *qc, real_t qd0, real_t qd1,
			real_t q0[], real_t q1[], int *nf,
			real_t (*funct)(int, real_t[]))
{


	int i;
	real_t *t,result;

	t=allocate_real_vector(1,n);
	if (j > 0)
		for (i=1; i<=n; i++) t[i]=x[i]+l*v[i][j];
	else {

		*qa=l*(l-qd1)/(qd0*(qd0+qd1));
		*qb=(l+qd0)*(qd1-l)/(qd0*qd1);
		*qc=l*(l+qd0)/(qd1*(qd0+qd1));
		for (i=1; i<=n; i++) t[i]=(*qa)*q0[i]+(*qb)*x[i]+(*qc)*q1[i];
	}
	(*nf)++;
	result=(*funct)(n,t);
	free_real_vector(t,1);
	return result;
}

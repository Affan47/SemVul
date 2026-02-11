symmeig(const MAT *A, MAT *Q, VEC *out)
#endif
{
	int	i;
	STATIC MAT	*tmp = MNULL;
	STATIC VEC	*b   = VNULL, *diag = VNULL, *beta = VNULL;

	if ( ! A )
		error(E_NULL,"symmeig");
	if ( A->m != A->n )
		error(E_SQUARE,"symmeig");
	if ( ! out || out->dim != A->m )
		out = v_resize(out,A->m);

	tmp  = m_resize(tmp,A->m,A->n);
	tmp  = m_copy(A,tmp);
	b    = v_resize(b,A->m - 1);
	diag = v_resize(diag,(unsigned int)A->m);
	beta = v_resize(beta,(unsigned int)A->m);
	MEM_STAT_REG(tmp,TYPE_MAT);
	MEM_STAT_REG(b,TYPE_VEC);
	MEM_STAT_REG(diag,TYPE_VEC);
	MEM_STAT_REG(beta,TYPE_VEC);

	Hfactor(tmp,diag,beta);
	if ( Q )
		makeHQ(tmp,diag,beta,Q);

	for ( i = 0; i < A->m - 1; i++ )
	{
		out->ve[i] = tmp->me[i][i];
		b->ve[i] = tmp->me[i][i+1];
	}
	out->ve[i] = tmp->me[i][i];
	trieig(out,b,Q);

#ifdef	THREADSAFE
	M_FREE(tmp);	V_FREE(b);	V_FREE(diag);	V_FREE(beta);
#endif
	return out;
}

_Qsolve(const MAT *QR, const VEC *diag, const VEC *b,
		 VEC *x, VEC *tmp)
#endif
{
    unsigned int	dynamic;
    int		k, limit;
    Real	beta, r_ii, tmp_val;

    limit = min(QR->m,QR->n);
    dynamic = FALSE;
    if ( ! QR || ! diag || ! b )
	error(E_NULL,"_Qsolve");
    if ( diag->dim < limit || b->dim != QR->m )
	error(E_SIZES,"_Qsolve");
    x = v_resize(x,QR->m);
    if ( tmp == VNULL )
	dynamic = TRUE;
    tmp = v_resize(tmp,QR->m);


    x = v_copy(b,x);
    for ( k = 0 ; k < limit ; k++ )
    {
	get_col(QR,k,tmp);
	r_ii = fabs(tmp->ve[k]);
	tmp->ve[k] = diag->ve[k];
	tmp_val = (r_ii*fabs(diag->ve[k]));
	beta = ( tmp_val == 0.0 ) ? 0.0 : 1.0/tmp_val;

	hhtrvec(tmp,beta,k,x,x);
    }

    if ( dynamic )
	V_FREE(tmp);

    return (x);
}

Hfactor(MAT *A, VEC *diag, VEC *beta)
#endif
{
	STATIC	VEC	*hh = VNULL, *w = VNULL;
	int	k, limit;

	if ( ! A || ! diag || ! beta )
		error(E_NULL,"Hfactor");
	if ( diag->dim < A->m - 1 || beta->dim < A->m - 1 )
		error(E_SIZES,"Hfactor");
	if ( A->m != A->n )
		error(E_SQUARE,"Hfactor");
	limit = A->m - 1;

	hh = v_resize(hh,A->m);
	w  = v_resize(w,A->n);
	MEM_STAT_REG(hh,TYPE_VEC);
	MEM_STAT_REG(w, TYPE_VEC);

	for ( k = 0; k < limit; k++ )
	  {

	    get_col(A,(unsigned int)k,hh);

	    hhvec(hh,k+1,&beta->ve[k],hh,&A->me[k+1][k]);

	    v_set_val(diag,k,v_entry(hh,k+1));


	    _hhtrcols(A,k+1,k+1,hh,v_entry(beta,k),w);
	    hhtrrows(A,0  ,k+1,hh,v_entry(beta,k));

	  }

#ifdef THREADSAFE
	V_FREE(hh);	V_FREE(w);
#endif

	return (A);
}

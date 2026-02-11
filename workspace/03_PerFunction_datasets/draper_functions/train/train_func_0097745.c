chk_col_access(const SPMAT *A)
#endif
{
    int		cnt_nz, j, row, idx;
    SPROW	*r;
    row_elt	*e;

    if ( ! A )
	error(E_NULL,"chk_col_access");


    cnt_nz = 0;
    for ( j = 0; j < A->n; j++ )
    {
	row = A->start_row[j];
	idx = A->start_idx[j];
	while ( row >= 0 )
	{
	    if ( row >= A->m || idx < 0 )
		return FALSE;
	    r = &(A->row[row]);
	    if ( idx >= r->len )
		return FALSE;
	    e = &(r->elt[idx]);
	    if ( e->nxt_row >= 0 && e->nxt_row <= row )
		return FALSE;
	    row = e->nxt_row;
	    idx = e->nxt_idx;
	    cnt_nz++;
	}
    }

    if ( cnt_nz != nonzeros(A) )
	return FALSE;
    else
	return TRUE;
}

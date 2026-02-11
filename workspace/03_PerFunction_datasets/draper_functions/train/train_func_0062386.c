scan_to(SPMAT *A, IVEC *scan_row, IVEC *scan_idx, IVEC *col_list,
		int max_row)
#endif
{
    int		col, idx, j_idx, row_num;
    SPROW	*r;
    row_elt	*e;

    if ( ! A || ! scan_row || ! scan_idx || ! col_list )
	error(E_NULL,"scan_to");
    if ( scan_row->dim != scan_idx->dim || scan_idx->dim != col_list->dim )
	error(E_SIZES,"scan_to");

    if ( max_row < 0 )
	return;

    if ( ! A->flag_col )
	sp_col_access(A);

    for ( j_idx = 0; j_idx < scan_row->dim; j_idx++ )
    {
	row_num = scan_row->ive[j_idx];
	idx = scan_idx->ive[j_idx];
	col = col_list->ive[j_idx];

	if ( col < 0 || col >= A->n )
	    error(E_BOUNDS,"scan_to");
	if ( row_num < 0 )
	{
	    idx = col;
	    continue;
	}
	r = &(A->row[row_num]);
	if ( idx < 0 )
	    error(E_INTERN,"scan_to");
	e = &(r->elt[idx]);
	if ( e->col != col )
	    error(E_INTERN,"scan_to");
	if ( idx < 0 )
	{
	    printf("scan_to: row_num = %d, idx = %d, col = %d\n",
		   row_num, idx, col);
	    error(E_INTERN,"scan_to");
	}


	while ( e->nxt_row >= 0 && e->nxt_row <= max_row )
	{
	    row_num = e->nxt_row;
	    idx = e->nxt_idx;
	    e = &(A->row[row_num].elt[idx]);
	}


	scan_row->ive[j_idx] = row_num;
	scan_idx->ive[j_idx] = idx;
    }
}

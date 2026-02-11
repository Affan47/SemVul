zset_row(mat,row,vec)
ZMAT	*mat;
ZVEC	*vec;
int	row;
{
	u_int	 lim;

	if ( mat==ZMNULL || vec==ZVNULL )
		error(E_NULL,"zset_row");
	if ( row < 0 || row >= mat->m )
		error(E_RANGE,"zset_row");
	lim = min(mat->n,vec->dim);


	MEMCOPY(vec->ve,mat->me[row],lim,complex);

	return (mat);
}

zget_col(mat,col,vec)
int	col;
ZMAT	*mat;
ZVEC	*vec;
{
	u_int	i;

	if ( mat==ZMNULL )
		error(E_NULL,"zget_col");
	if ( col < 0 || col >= mat->n )
		error(E_RANGE,"zget_col");
	if ( vec==ZVNULL || vec->dim<mat->m )
		vec = zv_resize(vec,mat->m);

	for ( i=0; i<mat->m; i++ )
	    vec->ve[i] = mat->me[i][col];

	return (vec);
}

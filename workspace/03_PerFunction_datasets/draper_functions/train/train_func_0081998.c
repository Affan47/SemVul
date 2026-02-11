zrot_cols(mat,i,k,c,s,out)
ZMAT	*mat,*out;
int	i,k;
double	c;
complex	s;
{
	u_int	j;
	complex	x, y;

	if ( mat==ZMNULL )
		error(E_NULL,"zrot_cols");
	if ( i < 0 || i >= mat->n || k < 0 || k >= mat->n )
		error(E_RANGE,"zrot_cols");
	out = zm_copy(mat,out);

	for ( j=0; j<mat->m; j++ )
	{
	    x = out->me[j][i];	y = out->me[j][k];

	    out->me[j][i].re = c*x.re - s.re*y.re - s.im*y.im;
	    out->me[j][i].im = c*x.im - s.re*y.im + s.im*y.re;


	    out->me[j][k].re = c*y.re + s.re*x.re - s.im*x.im;
	    out->me[j][k].im = c*y.im + s.re*x.im + s.im*x.re;
	}

	return (out);
}

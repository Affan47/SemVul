_v_norm1(x,scale)
VEC	*x, *scale;
{
	int	i, dim;
	Real	s, sum;

	if ( x == (VEC *)NULL )
		error(E_NULL,"_v_norm1");
	dim = x->dim;

	sum = 0.0;
	if ( scale == (VEC *)NULL )
		for ( i = 0; i < dim; i++ )
			sum += fabs(x->ve[i]);
	else if ( scale->dim < dim )
		error(E_SIZES,"_v_norm1");
	else
		for ( i = 0; i < dim; i++ )
		{	s = scale->ve[i];
			sum += ( s== 0.0 ) ? fabs(x->ve[i]) : fabs(x->ve[i]/s);
		}

	return sum;
}

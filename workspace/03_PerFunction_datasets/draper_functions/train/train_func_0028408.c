rot_cols(const MAT *mat,unsigned int i,unsigned int k,
		  double c, double s, MAT *out)
#endif
{
	unsigned int	j;
	Real	temp;

	if ( mat==(MAT *)NULL )
		error(E_NULL,"rot_cols");
	if ( i >= mat->n || k >= mat->n )
		error(E_RANGE,"rot_cols");
	if ( mat != out )
		out = m_copy(mat,m_resize(out,mat->m,mat->n));

	for ( j=0; j<mat->m; j++ )
	{

		temp = c*m_entry(out,j,i) + s*m_entry(out,j,k);

		m_set_val(out,j,k, -s*m_entry(out,j,i) + c*m_entry(out,j,k));

		m_set_val(out,j,i,temp);
	}

	return (out);
}

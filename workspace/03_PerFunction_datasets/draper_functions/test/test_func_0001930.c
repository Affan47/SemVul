rot_rows(mat,i,k,c,s,out)
MAT	*mat,*out;
u_int	i,k;
double	c,s;
{
	u_int	j;
	Real	temp;

	if ( mat==(MAT *)NULL )
		error(E_NULL,"rot_rows");
	if ( i >= mat->m || k >= mat->m )
		error(E_RANGE,"rot_rows");
	out = m_copy(mat,out);

	for ( j=0; j<mat->n; j++ )
	{

		temp = c*m_entry(out,i,j) + s*m_entry(out,k,j);

		m_set_val(out,k,j, -s*m_entry(out,i,j) + c*m_entry(out,k,j));

		m_set_val(out,i,j, temp);
	}

	return (out);
}

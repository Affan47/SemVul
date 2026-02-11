px_vec(PERM *px, const VEC *vector, VEC *out)
#endif
{
    unsigned int	old_i, i, size, start;
    Real	tmp;

    if ( px==PNULL || vector==VNULL )
	error(E_NULL,"px_vec");
    if ( px->size > vector->dim )
	error(E_SIZES,"px_vec");
    if ( out==VNULL || out->dim < vector->dim )
	out = v_resize(out,vector->dim);

    size = px->size;
    if ( size == 0 )
	return v_copy(vector,out);
    if ( out != vector )
    {
	for ( i=0; i<size; i++ )
	    if ( px->pe[i] >= size )
		error(E_BOUNDS,"px_vec");
	    else
		out->ve[i] = vector->ve[px->pe[i]];
    }
    else
    {
	start = 0;
	while ( start < size )
	{
	    old_i = start;
	    i = px->pe[old_i];
	    if ( i >= size )
	    {
		start++;
		continue;
	    }
	    tmp = vector->ve[start];
	    while ( TRUE )
	    {
		vector->ve[old_i] = vector->ve[i];
		px->pe[old_i] = i+size;
		old_i = i;
		i = px->pe[old_i];
		if ( i >= size )
		    break;
		if ( i == start )
		{
		    vector->ve[old_i] = tmp;
		    px->pe[old_i] = i+size;
		    break;
		}
	    }
	    start++;
	}

	for ( i = 0; i < size; i++ )
	    if ( px->pe[i] < size )
		error(E_BOUNDS,"px_vec");
	    else
		px->pe[i] = px->pe[i]-size;
    }

    return out;
}

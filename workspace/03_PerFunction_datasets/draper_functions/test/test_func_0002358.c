v_pconv(const VEC *x1, const VEC *x2, VEC *out)
#endif
{
    int		i;

    if ( ! x1 || ! x2 )
	error(E_NULL,"v_pconv");
    if ( x1 == out || x2 == out )
	error(E_INSITU,"v_pconv");
    out = v_resize(out,x2->dim);
    if ( x2->dim == 0 )
	return out;

    v_zero(out);
    for ( i = 0; i < x1->dim; i++ )
    {
	__mltadd__(&(out->ve[i]),x2->ve,x1->ve[i],x2->dim - i);
	if ( i > 0 )
	    __mltadd__(out->ve,&(x2->ve[x2->dim - i]),x1->ve[i],i);
    }

    return out;
}

iv_move(in,i0,dim0,out,i1)
IVEC	*in, *out;
int	i0, dim0, i1;
{
    if ( ! in )
	error(E_NULL,"iv_move");
    if ( i0 < 0 || dim0 < 0 || i1 < 0 ||
	 i0+dim0 > in->dim )
	error(E_BOUNDS,"iv_move");

    if ( (! out) || i1+dim0 > out->dim )
	out = iv_resize(out,i1+dim0);

    MEM_COPY(&(in->ive[i0]),&(out->ive[i1]),dim0*sizeof(int));

    return out;
}

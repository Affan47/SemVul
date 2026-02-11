DFGRsetimdims(int32 xdim, int32 ydim, int ncomps, int il)
{
    if (DFGRIsetil(il, IMAGE) < 0)
        return FAIL;
    return (DFGRIsetdims(xdim, ydim, ncomps, IMAGE));
}

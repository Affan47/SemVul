_dxfGetNeighbors(NeighborsHandle handle, int index, int *buf)
{
    int i, indices[10];

    _dxfGetIndices(index, handle->nDim, handle->nstrides, indices);

    for (i = 0; i < handle->nDim; i++)
    {
	if (indices[i] == 0)
	    if (handle->wrap & (1 << i))
		buf[i<<1] = index +
			(handle->gcounts[i]-1)*handle->nstrides[i];
	    else
		buf[i<<1] = -1;
	else
	    buf[i<<1] = index - handle->nstrides[i];

	if (indices[i] == (handle->gcounts[i]-1))
	    if (handle->wrap & (1 << i))
		buf[(i<<1)+1] = index -
			(handle->gcounts[i]-1)*handle->nstrides[i];
	    else
		buf[(i<<1)+1] = -1;
	else
	    buf[(i<<1)+1] = index + handle->nstrides[i];
    }

    return buf;
}

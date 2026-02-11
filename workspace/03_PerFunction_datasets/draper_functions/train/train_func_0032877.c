_dxfCleanup(TrisRI2DInterpolator ti)
{
    if (ti->fieldInterpolator.localized)
    {
	if (ti->neighbors)
	    DXFreeArrayDataLocal(ti->nArray, (Pointer)ti->neighbors);
	if (ti->triangles)
	    DXFreeArrayDataLocal(ti->tArray, (Pointer)ti->triangles);
    }

    ti->neighbors = NULL;
    ti->triangles = NULL;

    if (ti->pHandle)
    {
	DXFreeArrayHandle(ti->pHandle);
	ti->pHandle = NULL;
    }

    if (ti->dHandle)
    {
	DXFreeArrayHandle(ti->dHandle);
	ti->dHandle = NULL;
    }

    if (ti->dArray)
    {
	DXDelete((Object)ti->dArray);
	ti->dArray = NULL;
    }

    if (ti->pArray)
    {
	DXDelete((Object)ti->pArray);
	ti->pArray = NULL;
    }

    if (ti->nArray)
    {
	DXDelete((Object)ti->nArray);
	ti->nArray = NULL;
    }

    if (ti->tArray)
    {
	DXDelete((Object)ti->tArray);
	ti->tArray = NULL;
    }

    if (ti->grid)
    {
	_dxfFreeSearchGrid(ti->grid);
	ti->grid = NULL;
    }

    return OK;
}

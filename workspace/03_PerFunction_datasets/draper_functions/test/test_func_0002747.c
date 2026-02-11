PolylineFieldVolume(Field field)
{
    Array pArray, plArray, eArray;
    int   i, j, pDim;
    float buf0[32], buf1[32];
    float *ptrs[2];
    int   nPolylines, nEdges, *polylines, *edges;
    ArrayHandle pHandle;
    float fvol;

    pArray = (Array)DXGetComponentValue(field, "positions");
    if (! pArray)
    {
	DXSetError(ERROR_MISSING_DATA, "missing positions");
	goto error;
    }

    plArray = (Array)DXGetComponentValue(field, "polylines");
    if (! plArray)
    {
	DXSetError(ERROR_MISSING_DATA, "missing polylines");
	goto error;
    }

    eArray = (Array)DXGetComponentValue(field, "edges");
    if (! eArray)
    {
	DXSetError(ERROR_MISSING_DATA, "polylines but no edges");
	goto error;
    }

    DXGetArrayInfo(plArray, &nPolylines, NULL, NULL, NULL, NULL);
    DXGetArrayInfo(eArray, &nEdges, NULL, NULL, NULL, NULL);
    DXGetArrayInfo(pArray, NULL, NULL, NULL, NULL, &pDim);

    polylines = (int *)DXGetArrayData(plArray);
    edges     = (int *)DXGetArrayData(eArray);

    pHandle = DXCreateArrayHandle(pArray);

    for (i = 0, fvol = 0.0; i < nPolylines; i++)
    {
	int start = polylines[i];
	int end   = (i == nPolylines-1) ? nEdges : polylines[i+1];
	int knt   = (end - start) - 1;
	int *seg  = edges + start;

	ptrs[1] = (float *)DXGetArrayEntry(pHandle, *seg, buf1);

	for (j = 0, seg++; j < knt; j++, seg++)
	{
	    ptrs[0] = ptrs[1];
	    ptrs[1] = (float *)DXGetArrayEntry(pHandle, *seg,
			    (j & 0x1) ? buf1 : buf0);

	    fvol += LineLength(ptrs, pDim);
	}
    }

    pHandle = NULL;

    return fvol;

error:
    return -1;
}

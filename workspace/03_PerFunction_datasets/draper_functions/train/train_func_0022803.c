InvalidateBoundaryDuplicates(Pointer ptr)
{
    IJ        ij;
    Externals *externals, ei, ej;
    int       i, j, k, n;
    Field     field;
    byte      *flags = NULL;
    ExVert    xv;
    InvalidComponentHandle ich = NULL;


    if ((i = ((Task1Params)ptr)->i) == 0)
	return OK;

    field	= ((Task1Params)ptr)->field;
    ij   	= ((Task1Params)ptr)->ij;
    externals   = ((Task1Params)ptr)->externals;

    ei = externals[i];


    InitGetNextExternalVertex(ei);
    for (n = 0; NULL != GetNextExternalVertex(ei); n++);
    if (n == 0)
	 return OK;

    flags = (byte *)DXAllocateZero(n*sizeof(byte));
    if (! flags)
	 goto error;

    for (j = 0; j < i; j++)
    {
	if (ij[j].neighbor == 0)
	    continue;

	ej = externals[j];

	InitGetNextExternalVertex(ei);
	for (k = 0; NULL != (xv = GetNextExternalVertex(ei)); k++)
	    if (! flags[k] && QueryExternals(ej, xv->point))
		flags[k] = 1;
    }

    ich = DXCreateInvalidComponentHandle((Object)field, NULL, "positions");
    if (! ich)
	goto error;

    InitGetNextExternalVertex(ei);
    for (k = 0; NULL != (xv = GetNextExternalVertex(ei)); k++)
	if (flags[k])
	    DXSetElementInvalid(ich, xv->vIndex);

    if (! DXSaveInvalidComponent(field, ich))
	goto error;

    DXFree((Pointer)flags);
    DXFreeInvalidComponentHandle(ich);

    return OK;

error:
    DXFree((Pointer)flags);
    return ERROR;
}

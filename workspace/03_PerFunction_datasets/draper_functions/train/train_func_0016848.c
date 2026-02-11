PickInterpolate(Object object, Field picks, int flag)
{
    Array array, wArray = NULL;
    PickWts *wPtr;
    Point *point;
    int npokes, npicks;
    int i, j;

    if (DXEmptyField(picks))
	return OK;

    array = (Array)DXGetComponentValue(picks, "positions");
    point = (Point *)DXGetArrayData(array);

    wArray = (Array)DXGetComponentValue(picks, "pick weights");
    if (! wArray)
    {
	DXSetError(ERROR_MISSING_DATA, "pick weights");
	goto error;
    }

    DXReference((Object)wArray);
    DXDeleteComponent(picks, "pick weights");

    wPtr = (PickWts *)DXGetArrayData(wArray);

    if (! DXQueryPokeCount(picks, &npokes))
	goto error;

    for (i = 0; i < npokes; i++)
    {

	if (! DXQueryPickCount(picks, i, &npicks))
	    goto error;

	for (j = 0; j < npicks; j++, point++)
	{
	    int *path, elt, vert, length;
	    float *wts = (float *)(wPtr + 1);

	    if (! DXQueryPickPath(picks, i, j, &length, &path, &elt, &vert))
		goto error;

	    if (! PickTraverse(object, NULL, *point, path, length, elt,
				vert, picks, flag, wPtr->segment, wts))
		goto error;

	    wPtr = (PickWts *)(((char *)wPtr)+sizeof(PickWts)+wPtr->nweights*sizeof(float));
	}
    }

    DXDelete((Object)wArray);
    return OK;

error:
    DXDelete((Object)wArray);
    return ERROR;
}

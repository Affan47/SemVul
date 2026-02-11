AlignStartPtsAndTimes(Array starts, Array times)
{
    int nStarts, nTimes;

    DXGetArrayInfo(starts, &nStarts, NULL, NULL, NULL, NULL);
    DXGetArrayInfo(times,  &nTimes, NULL, NULL, NULL, NULL);

    if (nStarts == nTimes)
	return OK;
    else if (nStarts == 1)
    {
	int itemSize = DXGetItemSize(starts);
	int i;
	unsigned char *src, *dst;

	if (! DXAddArrayData(starts, 1, nTimes-1, NULL))
	    goto error;

	src = (unsigned char *)DXGetArrayData(starts);
	dst = src + itemSize;
	for (i = 0; i < nTimes; i++, dst += itemSize)
	     memcpy(dst, src, itemSize);
    }
    else if (nTimes == 1)
    {
	int itemSize = DXGetItemSize(times);
	int i;
	unsigned char *src, *dst;

	if (! DXAddArrayData(times, 1, nStarts-1, NULL))
	    goto error;

	src = (unsigned char *)DXGetArrayData(times);
	dst = src + itemSize;
	for (i = 0; i < nStarts; i++, dst += itemSize)
	     memcpy(dst, src, itemSize);
    }
    else
    {
	DXSetError(ERROR_BAD_PARAMETER, "#11160",
		"start positions", nStarts, "start times", nTimes);
	goto error;
    }

    return OK;

error:
    return ERROR;
}

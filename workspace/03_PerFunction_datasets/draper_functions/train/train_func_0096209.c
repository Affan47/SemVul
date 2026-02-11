QuadsWalk(QuadArgs *args, int quadIndex)
{
    int  	  side;
    int           *quad;
    int		  knt;
    int		  nbr;
    ArrayHandle	  pHandle;
    ArrayHandle   qHandle;
    int		  *visited, vCount;
    int		  limit;
    int		  fuzzFlag;
    int		  *vPtr;

    pHandle  = args->pHandle;
    qHandle  = args->qHandle;
    visited  = args->visited;
    vCount   = args->vCount;
    limit    = args->limit;
    fuzzFlag = args->fuzzFlag;

    for (knt = 0; quadIndex != -1 && knt < limit; knt++, quadIndex = nbr)
    {
	float pbuf[2], qbuf[2], rbuf[2], sbuf[2];

	if (visited)
	{
	    vPtr = visited + quadIndex;

	    if (*vPtr == vCount)
		break;
	    else
		*vPtr = vCount;
	}

	quad = (int *)DXGetArrayEntry(qHandle, quadIndex,
						    (Pointer)(args->quad));

	args->quadPoints[0]  =
	    (float *)DXGetArrayEntry(pHandle, quad[0], (Pointer)pbuf);

	args->quadPoints[1]  =
	    (float *)DXGetArrayEntry(pHandle, quad[1], (Pointer)qbuf);

	args->quadPoints[2]  =
	    (float *)DXGetArrayEntry(pHandle, quad[2], (Pointer)rbuf);

	args->quadPoints[3]  =
	    (float *)DXGetArrayEntry(pHandle, quad[3], (Pointer)sbuf);

	side = quad_coords(args);

	if (side == ZERO_AREA)
	    break;

	if (side == INSIDE || (fuzzFlag == FUZZ_ON && WithinFuzz(side)))
	{
	    if (quad != args->quad)
		memcpy(args->quad, quad, 4*sizeof(int));

	    return quadIndex;
	}

	nbr = quadExit(args, side, quadIndex);
	if (nbr == -1)
	    return -1;
    }

    return -1;
}

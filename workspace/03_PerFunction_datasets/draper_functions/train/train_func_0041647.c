_dxfTetraSearch(TetraArgs *args, int index)
{
    int  	nbr;
    int  	side;
    Tetrahedron	*tet;
    int		knt;
    int		*vPtr;
    ArrayHandle	points;
    Tetrahedron	*tetras;
    int		*visited, vCount;
    int		limit;
    int		fuzzFlag;
    Point	ptBuf[4];

    points    = args->points;
    tetras    = args->tetras;
    visited   = args->visited;
    vCount    = args->vCount;
    limit     = args->limit;
    fuzzFlag  = args->fuzzFlag;

    nbr = 0;

    for (knt = 0; index != -1 && knt < limit; knt++, index = nbr)
    {
	if (visited)
	{
	    vPtr = visited + index;

	    if (*vPtr == vCount)
		break;
	    else
		*vPtr = vCount;
	}

	tet = tetras + index;

	args->p0  = (Point *)
		    DXGetArrayEntry(points, tet->p, (Pointer)(ptBuf+0));
	args->p1  = (Point *)
		    DXGetArrayEntry(points, tet->q, (Pointer)(ptBuf+1));
	args->p2  = (Point *)
		    DXGetArrayEntry(points, tet->r, (Pointer)(ptBuf+2));
	args->p3  = (Point *)
		    DXGetArrayEntry(points, tet->s, (Pointer)(ptBuf+3));

#ifdef DIAG
	nT ++;
#endif

	side = _dxfbarycentric_coords(args);


	if (side == ZERO_VOLUME)
	     break;

	if (side == INSIDE)
	    return index;


	if (fuzzFlag == FUZZ_ON && WithinFuzz(side))
	    return index;


	if (knt < (limit-1))
	{
	    nbr = _dxfbaryExit(side, index, args);
	    if (nbr < 0)
		return -1;
	}

	if (! _dxfBBoxTest(args, nbr))
	    return -1;
    }

    return -1;
}

GrowRegularGrid(Array oArray, LoHi growth)
{
    int   oCounts[3], nCounts[3];
    float oOrigin[3], nOrigin[3];
    float deltas[9], *d;
    Array nArray;
    int   nDim, oDim, i, j;

    DXQueryGridPositions(oArray, &nDim, oCounts, oOrigin, deltas);


    for (i = 0; i < nDim; i++)
	nOrigin[i] = oOrigin[i];

    d = deltas; oDim = 0;
    for (i = 0; i < nDim; i++)
    {
	if (oCounts[i] > 1)
	{


	    nCounts[i] = oCounts[i] + (growth[oDim].lo+growth[oDim].hi);


	    if (growth[oDim].lo)
		for (j = 0; j < nDim; j++)
		    nOrigin[j] -= growth[oDim].lo * *d++;
	    else
		d += nDim;

	    oDim ++;
	}
	else
	{
	    nCounts[i] = 1;
	    d += nDim;
	}
    }

    nArray = DXMakeGridPositionsV(nDim, nCounts, nOrigin, deltas);
    return nArray;
}

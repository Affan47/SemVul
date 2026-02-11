Irreg_FindElement(InstanceVars I, POINT_TYPE *point)
{
    int i, last, r = 0;
    Irreg_InstanceVars iI = (Irreg_InstanceVars)I;
    Irreg_VectorGrp    iP = (Irreg_VectorGrp)(iI->i.currentVectorGrp);

    last = iI->cp;

    for (i = 0; i < iP->P.n; i++)
	if (last != i && iP->P.p[i] != NULL
			&& _dxfIsInBox(iP->P.p[i], point, iP->P.nDim, 0))
	{
	    if ((r = Irreg_FindElement_VectorPart(iI, i, point)) != 0)
		break;
	}

    if (r == -1)
	return -1;
    else if (i == iP->P.n)
	return 0;
    else
    {
        if (I->currentPartition)
	     DXDelete(I->currentPartition);
	I->currentPartition = DXReference((Object)iP->P.p[i]->field);
	return 1;
    }
}

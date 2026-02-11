Reg_FindElement(InstanceVars I, POINT_TYPE *point)
{
    int i;
    Reg_InstanceVars iI = (Reg_InstanceVars)I;
    Reg_VectorGrp    iP = (Reg_VectorGrp)I->currentVectorGrp;

    for (i = 0; i < iP->P.n; i++)
	if (_dxfIsInBox(iP->P.p[i], point, iP->P.nDim, 0))
	{
	    if (Reg_FindElement_VectorPart(iI, i, point))
		break;
	}

    if (i == iP->P.n)
	return 0;
    else
    {
        if (I->currentPartition)
	    DXDelete(I->currentPartition);
	I->currentPartition = DXReference((Object)iP->P.p[i]->field);
	return 1;
    }
}

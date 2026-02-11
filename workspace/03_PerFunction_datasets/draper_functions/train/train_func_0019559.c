OrientTriangles(Field field, Vector *n)
{
    Array pA, cA;
    float *points;
    int   *tri, i;
    int   nPoints, nTriangles;

    if (DXEmptyField(field))
	return OK;

    pA = (Array)DXGetComponentValue(field, "positions");
    cA = (Array)DXGetComponentValue(field, "connections");


    if (! DXGetArrayInfo(pA, &nPoints, NULL, NULL, NULL, NULL))
	goto error;

    if (! DXGetArrayInfo(cA, &nTriangles, NULL, NULL, NULL, NULL))
	goto error;

    points = (float *)DXGetArrayData(pA);
    tri    = (int *)DXGetArrayData(cA);

    for (i = 0; i < nTriangles; i++, tri += 3)
    {
	float *p = points+3*tri[0];
	float *q = points+3*tri[1];
	float *r = points+3*tri[2];
	if (Orientation(p, q, r, n) == MIS_ALIGNED)
	{
	    int t = tri[0];
	    tri[0] = tri[1];
	    tri[1] = t;
	}
    }

    return OK;

error:
    return ERROR;
}

Elt0D_Perspective(PickBuf *pick, int poke, Point2D xy, Point *xPoints,
			int nPts, float nearPlane, float sens, float min, float max)
{
    int i;
    Point2D *sPoints;

    sPoints = (Point2D *)DXAllocate(nPts*sizeof(Point2D));
    if (! sPoints)
	goto error;

    nearPlane += ZOFFSET;


    for (i = 0; i < nPts; i++)
    {
	float z = xPoints[i].z;
	if (z < nearPlane)
	{
	    float invDepth = 1.0 / (-z + ZOFFSET);
	    sPoints[i].x = xPoints[i].x * invDepth;
	    sPoints[i].y = xPoints[i].y * invDepth;
	}
    }

    for (i = 0; i < nPts; i++)
    {
	if (xPoints[i].z < nearPlane &&
	    fabs(sPoints[i].x - xy.x) < sens &&
	    fabs(sPoints[i].y - xy.y) < sens)
	{
	    if (xPoints[i].z > min && xPoints[i].z < max)
	    {
		pick->pickPath[pick->depth+0] = i;
		pick->pickPath[pick->depth+1] = i;
		if (! AddPick(pick, poke, xPoints[i], 0, -1, NULL))
		    goto error;
	    }
	}
    }

    DXFree((Pointer)sPoints);
    return OK;

error:
    DXFree((Pointer)sPoints);
    return ERROR;
}

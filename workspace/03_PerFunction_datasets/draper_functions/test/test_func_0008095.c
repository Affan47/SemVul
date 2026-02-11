MapArrays_PDep_Grid_Irreg(Array old, SegList *iBuf)
{
    Array        new=NULL;
    Vector       *base;
    Intercept    *ix;
    int		 c[3];
    Vector	 o, d[3];
    int		 zknt, yknt;

    if (! DXQueryGridPositions(old, NULL, c, (float *)&o, (float *)d))
	goto error;

    zknt = c[2];
    yknt = c[1];

    new = DXNewArray(TYPE_FLOAT, CATEGORY_REAL, 1, 3);
    if (! new)
	goto error;

    if (! DXAddArrayData(new, 0, DXGetSegListItemCount(iBuf), NULL))
	goto error;

    base = (Vector *)DXGetArrayData(new);

    if (! DXInitGetNextSegListItem(iBuf))
	goto error;

    while (NULL != (ix = (Intercept *)DXGetNextSegListItem(iBuf)))
    {
	Vector p0, p1, *dst = base + ix->index;
	int jj;
	float x, y, z;

	z  = ix->i0  % zknt;
	jj = ix->i0  / zknt;
	y  =    jj % yknt;
	x  =    jj / yknt;

	ADDMULVECTOR(d[0], x,  o, p0);
	ADDMULVECTOR(d[1], y, p0, p0);
	ADDMULVECTOR(d[2], z, p0, p0);

	if (ix->i1 != -1)
	{
	    z  = ix->i1  % zknt;
	    jj = ix->i1  / zknt;
	    y  =    jj % yknt;
	    x  =    jj / yknt;

	    ADDMULVECTOR(d[0], x,  o, p1);
	    ADDMULVECTOR(d[1], y, p1, p1);
	    ADDMULVECTOR(d[2], z, p1, p1);

	    dst->x = p0.x + ix->d*(p1.x - p0.x);
	    dst->y = p0.y + ix->d*(p1.y - p0.y);
	    dst->z = p0.z + ix->d*(p1.z - p0.z);
	}
	else
	    *dst = p0;
    }

    return new;

error:
    DXDelete((Object)new);
    return NULL;
}

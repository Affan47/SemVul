MapArrays_PDep_Grid_Reg(Array old, SegList *iBuf, Matrix *mat)
{
    Array        new;
    Vector       *base;
    RegIntercept *x;
    float        A00, A01, A02, A10, A11, A12, A20, A21, A22;
    float        B0, B1, B2;
    float        X=0, Y=0, Z=0;

    new = DXNewArray(TYPE_FLOAT, CATEGORY_REAL, 1, 3);
    if (! new)
	goto error;

    if (! DXAddArrayData(new, 0, DXGetSegListItemCount(iBuf), NULL))
	goto error;

    base = (Vector *)DXGetArrayData(new);

    if (! DXInitGetNextSegListItem(iBuf))
	goto error;

    A00 = mat->A[0][0]; A01 = mat->A[0][1]; A02 = mat->A[0][2];
    A10 = mat->A[1][0]; A11 = mat->A[1][1]; A12 = mat->A[1][2];
    A20 = mat->A[2][0]; A21 = mat->A[2][1]; A22 = mat->A[2][2];

    B0 = mat->b[0]; B1 = mat->b[1]; B2 = mat->b[2];

    while (NULL != (x = (RegIntercept *)DXGetNextSegListItem(iBuf)))
    {
	Vector *dst = base + x->x.index;

	switch(x->axis)
	{
	    case XAXIS:
		X = x->intercept;
		Y = x->i;
		Z = x->j;
		break;

	    case YAXIS:
		X = x->i;
		Y = x->intercept;
		Z = x->j;
		break;

	    case ZAXIS:
		X = x->i;
		Y = x->j;
		Z = x->intercept;
		break;
	}

	dst->x = A00*X + A10*Y + A20*Z + B0;
	dst->y = A01*X + A11*Y + A21*Z + B1;
	dst->z = A02*X + A12*Y + A22*Z + B2;
    }

    return new;

error:
    DXDelete((Object)new);
    return NULL;
}

MapArrays_PDep_Irreg(Array old, SegList *iBuf)
{
    Array        new = NULL;
    Intercept    *x;
    Type         t;
    Category     c;
    int          r, s[32];
    ArrayHandle  oHandle = NULL;
    Pointer	 oScratch0 = NULL, oScratch1;

    DXGetArrayInfo(old, NULL, &t, &c, &r, s);

    new = DXNewArrayV(t, c, r, s);
    if (! new)
	goto error;

    if (! DXAddArrayData(new, 0, DXGetSegListItemCount(iBuf), NULL))
	goto error;

    oHandle = DXCreateArrayHandle(old);
    if (! oHandle)
	goto error;

    oScratch0 = DXAllocate(2*DXGetItemSize(old));
    if (! oScratch0)
	goto error;

    oScratch1 = (Pointer)((char *)oScratch0 + DXGetItemSize(old));

    switch(t)
    {
	case TYPE_DOUBLE:
	     INTERPOLATE_INTERCEPT(double, 0.0);
	     break;
	case TYPE_FLOAT:
	     INTERPOLATE_INTERCEPT(float, 0.0);
	     break;
	case TYPE_INT:
	     INTERPOLATE_INTERCEPT(int, 0.5);
	     break;
	case TYPE_UINT:
	     INTERPOLATE_INTERCEPT(uint, 0.5);
	     break;
	case TYPE_SHORT:
	     INTERPOLATE_INTERCEPT(short, 0.5);
	     break;
	case TYPE_USHORT:
	     INTERPOLATE_INTERCEPT(ushort, 0.5);
	     break;
	case TYPE_BYTE:
	     INTERPOLATE_INTERCEPT(byte, 0.5);
	     break;
	case TYPE_UBYTE:
	     INTERPOLATE_INTERCEPT(ubyte, 0.5);
	     break;
	default:
	     DXSetError(ERROR_DATA_INVALID, "#10320", "data");
	     goto error;
    }

    DXFreeArrayHandle(oHandle);
    DXFree(oScratch0);

    return new;

error:
    DXFreeArrayHandle(oHandle);
    DXFree(oScratch0);
    DXDelete((Object)new);
    return NULL;
}

CopyArray(Array in)
{
    int      nIn;
    Array    out=NULL;
    Type     type;
    Category cat;
    int	     rank, shape[32];

    if (DXGetObjectClass((Object)in) != CLASS_ARRAY)
	goto error;

    DXGetArrayInfo(in, &nIn, &type, &cat, &rank, shape);


    if (DXQueryConstantArray(in, NULL, NULL))
	return in;


    out = DXNewArrayV(type, cat, rank, shape);
    if (! out)
	goto error;

    if (! DXAddArrayData(out, 0, nIn, DXGetArrayData(in)))
	goto error;


    return out;

error:
    if (out)
	DXDelete((Object)out);

    return NULL;
}

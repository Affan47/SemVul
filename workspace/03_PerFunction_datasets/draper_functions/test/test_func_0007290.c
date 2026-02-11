DefaultOrigin(Array driver)
{
    float p[32];
    Array a = NULL;
    int dim, i, r;

    if (driver)
    {
	DXGetArrayInfo(driver, NULL, NULL, NULL, &r, &dim);
	if (r == 0)
	    dim = 1;
    }
    else
	dim = 3;

    a = DXNewArray(TYPE_FLOAT, CATEGORY_REAL, 1, dim);
    if (! a)
	goto error;

    for (i = 0; i < dim; i++)
	p[i] = 0.0;

    if (! DXAddArrayData(a, 0, 1, (Pointer)p))
	goto error;

    return a;

error:
    DXDelete((Object)a);
    return NULL;
}

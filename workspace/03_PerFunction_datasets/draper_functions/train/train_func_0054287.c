q1dNd(Object o, char *cn)
{
    int i, j, n;
    int rank, shape;
    Field f;
    Object data;

    n = atoi(cn);

    if (DXGetObjectClass(o) == CLASS_ARRAY) {
	if (!DXGetArrayInfo((Array)o, NULL, NULL, NULL, &rank, NULL))
	    return 0;

	if (rank != 1)
	    return 0;

	if (!DXGetArrayInfo((Array)o, NULL, NULL, NULL, &rank, &shape))
	    return 0;

	if (n != shape)
	    return 0;

	return 1;
    }

    for (i=0, j=0; (f=getpartplus(o, &i, &j)); ) {

	if (!(data = DXGetComponentValue(f, "data")))
	    return 0;

	if (DXGetObjectClass(data) != CLASS_ARRAY)
	    return 0;

	if (!DXGetArrayInfo((Array)data, NULL, NULL, NULL, &rank, NULL))
	    return 0;

	if (rank != 1)
	    return 0;

	if (!DXGetArrayInfo((Array)data, NULL, NULL, NULL, &rank, &shape))
	    return 0;

	if (n != shape)
	    return 0;
    }

    return (j > 0) ? 1 : 0;
}

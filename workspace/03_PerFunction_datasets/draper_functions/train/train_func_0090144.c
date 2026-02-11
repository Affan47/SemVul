RegularData(Array a)
{
    Type type;
    Category cat;
    int rank;
    int shape[MAXDIM];


    if (DXGetArrayClass(a) != CLASS_REGULARARRAY)
	return ERROR;

    if (!DXGetArrayInfo(a, NULL, &type, &cat, &rank, shape))
	return ERROR;

    if (cat != CATEGORY_REAL || rank >= 2)
	return ERROR;

    if (rank == 1 && shape[0] != 1)
	return ERROR;

    return OK;
}

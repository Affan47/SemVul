_dxfRecognizeLinesII1D(Field field)
{
    Array    array;
    int      rank, shape[32];
    Type     type;
    Category cat;

    CHECK(field, CLASS_FIELD);

    ELT_TYPECHECK(field, "lines");

    array = (Array)DXGetComponentValue(field, "positions");
    if (!array)
    {
	DXSetError(ERROR_MISSING_DATA, "#10240", "positions");
	return 0;
    }

    DXGetArrayInfo(array, NULL, &type, &cat, &rank, shape);

    if (rank != 0 && (rank != 1 || shape[0] != 1))
    {
	DXSetError(ERROR_DATA_INVALID, "#11003", "lines", 1);
	return 0;
    }

    array = (Array)DXGetComponentValue(field, "connections");
    if (!array)
    {
	DXSetError(ERROR_MISSING_DATA, "#10240", "positions");
	return 0;
    }
    else
    {
	DXGetArrayInfo(array, NULL, &type, &cat, &rank, shape);

	if (type != TYPE_INT)
	{
	    DXSetError(ERROR_DATA_INVALID, "#11450");
	    return 0;
	}

	if (cat != CATEGORY_REAL)
	{
	    DXSetError(ERROR_DATA_INVALID, "#11450");
	    return 0;
	}
    }

    return 1;
}

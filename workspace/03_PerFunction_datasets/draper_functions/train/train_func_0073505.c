_dxfRecognizeQuadsII2D(Field field)
{
    Array    array;
    Type t;
    Category c;
    int r, s[32];

    CHECK(field, CLASS_FIELD);

    ELT_TYPECHECK(field, "quads");

    array = (Array)DXGetComponentValue(field, "positions");
    if (! array)
	return 0;

    DXGetArrayInfo(array, NULL, &t, &c, &r, s);

    if (t != TYPE_FLOAT || c != CATEGORY_REAL || r != 1)
    {
	DXSetError(ERROR_DATA_INVALID, "#11450");
	return 0;
    }

    if (s[0] != 2)
    {
	DXSetError(ERROR_DATA_INVALID, "#11363", "quads", 2);
	return 0;
    }

    array = (Array)DXGetComponentValue(field, "connections");
    if (! array)
	return 0;

    DXGetArrayInfo(array, NULL, &t, &c, &r, s);

    if (t != TYPE_INT || c != CATEGORY_REAL || r != 1)
    {
	DXSetError(ERROR_DATA_INVALID, "#11450");
	return 0;
    }

    if (s[0] != 4)
    {
	DXSetError(ERROR_DATA_INVALID, "#11004", "quads", 2);
	return 0;
    }

    return 1;
}

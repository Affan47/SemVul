Cubes2Tetrahedra(Field field)
{
    Array cArray;

    if (DXEmptyField(field))
	return field;

    cArray = (Array)DXGetComponentValue(field, "connections");
    if (! cArray)
    {
	DXSetError(ERROR_MISSING_DATA, "#10240", "connections");
	return NULL;
    }

    if (DXQueryGridConnections(cArray, NULL, NULL))
	field = RegCubes2Tetrahedra(field);
    else
	field = IrregCubes2Tetrahedra(field);

    if (! field)
	return NULL;

    if (! DXSetComponentAttribute(field, "connections", "element type",
				(Object)DXNewString("tetrahedra")))
	return NULL;

    return field;
}

_dxfPositionNormals_Field(Field field)
{
    Array		array;
    int			rank, shape[10];
    Type		type;
    Category		cat;
    int			n;
    char		*primitive;
    Object 		attr;


    if (DXEmptyField(field))
	return OK;

    array = (Array)DXGetComponentValue(field, "connections");
    if (! array)
	return OK;

    DXGetArrayInfo(array, &n, NULL, NULL, NULL, NULL);
    if (n <= 0)
	return OK;

    DXDeleteComponent(field, "normals");

    array = (Array)DXGetComponentValue(field, "positions");
    if (! array)
    {
	DXSetError(ERROR_DATA_INVALID, "#10200", "positions component");
	return ERROR;
    }

    DXGetArrayInfo(array, &n, &type, &cat, &rank, shape);

    if (rank != 1 || shape[0] < 2 || shape[0] > 3)
    {
	DXSetError(ERROR_DATA_INVALID, "positions must be 2 or 3-D");
	return ERROR;
    }

    if (shape[0] == 2)
    {
        float normal[3] = {0.0, 0.0, 1.0};
	array = (Array)DXNewConstantArray(n, (Pointer)normal,
		TYPE_FLOAT, CATEGORY_REAL, 1, 3);
    }
    else
    {
	attr = DXGetComponentAttribute(field, "connections", "element type");
	if (!attr)
	{
	    DXSetError(ERROR_DATA_INVALID, "#10255",
				    "connections", "element type");
	    return ERROR;
	}

	if (DXGetObjectClass(attr) != CLASS_STRING)
	{
	    DXSetError(ERROR_DATA_INVALID, "#10200", "element type attribute");
	    return ERROR;
	}


	primitive = DXGetString((String)attr);

	if (! strcmp(primitive, "triangles"))
	    array =_dxf_PDep_triangles(field);
	else if (! strcmp(primitive, "quads"))
	    array =_dxf_PDep_quads(field);
	else
	    array = NULL;
    }

    if (array)
    {


	if (DXGetComponentValue(field, "original normals"))
	    DXDeleteComponent(field, "original normals");

	if (! (DXSetComponentValue(field, "normals",(Object)array) &&
	       DXChangedComponentValues(field, "normals")	       &&
	       DXEndField(field)))
	    return ERROR;
    }

    return OK;
}

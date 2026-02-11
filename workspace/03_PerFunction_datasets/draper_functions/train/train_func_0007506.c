_dxfValidInterpolatorMap(Object map)
{
    char *name;
    Class class;

    name = NULL;

    class = DXGetObjectClass(map);
    if (class == CLASS_GROUP)
	class = DXGetGroupClass((Group)map);

    if (class == CLASS_COMPOSITEFIELD || class == CLASS_MULTIGRID)
    {
	Object  child;
	int	i;

	i = 0;
	while (NULL != (child = DXGetEnumeratedMember((Group)map, i++, NULL)))
	    if (! _dxfValidInterpolatorMap(child))
		return ERROR;

	return OK;
    }
    else if (class == CLASS_XFORM)
    {
	Object c;

	if (! DXGetXformInfo((Xform)map, &c, NULL))
	    return ERROR;

	return _dxfValidInterpolatorMap(c);
    }
    else if (class == CLASS_FIELD)
    {
	struct PrimTypes *prim;
	Array  		 array;
	int   		 rank, shape[32];
	int		 nPrims;
	Object		 at;


	if (DXEmptyField((Field)map))
	    return OK;

	array = (Array)DXGetComponentValue((Field)map, "connections");
	if (! array)
	    return OK;

	DXGetArrayInfo(array, &nPrims, NULL, NULL, NULL, NULL);
	if (nPrims < 0)
	    return OK;

	at = DXGetComponentAttribute((Field)map, "connections", "element type");
	if (! at || DXGetObjectClass(at) != CLASS_STRING)
	{
	    DXSetError(ERROR_MISSING_DATA, "#10255", "connections",
							"element type");
	    return ERROR;
	}

	name = DXGetString((String)at);

	for (prim = _dxdprimTypes; prim->name != NULL; prim ++)
	    if (! strcmp(prim->name, name))
		break;

	if (prim->name == NULL)
	{
	    DXSetError(ERROR_DATA_INVALID, "#11380", "name");
	    return ERROR;
	}

	array = (Array)DXGetComponentValue((Field)map, "positions");
	if (! array)
	{
	    DXSetError(ERROR_MISSING_DATA, "#10240", "map", "positions");
	    return ERROR;
	}

	DXGetArrayInfo(array, NULL, NULL, NULL, NULL, shape);

	if (shape[0] != prim->dimensionality)
	{
	    DXSetError(ERROR_DATA_INVALID, "#11003",
				    prim->name, prim->dimensionality);
	    return ERROR;
	}

	array = (Array)DXGetComponentValue((Field)map, "connections");
	DXGetArrayInfo(array, NULL, NULL, NULL, &rank, shape);

	if (rank != 1 || shape[0] != prim->ptsPerPrimitive)
	{
	    DXSetError(ERROR_DATA_INVALID, "#11004",
			prim->name, prim->ptsPerPrimitive);
	    return ERROR;
	}

	return OK;
    }
    else
    {
	DXSetError(ERROR_DATA_INVALID, "#11381");
	return ERROR;
    }
}

traverse(Object o, struct arg *arg)
{
    int             i, inType;
    Object          oo;
    unsigned char  *src;
    Array           colorArray;
    Array           connections;
    Type            type;
    int	            rank, shape[32];
    int		    offsets[2];
    int		    pcounts[2];

    switch (DXGetObjectClass((Object)o)) {

	case CLASS_GROUP:

	    if (DXGetGroupClass((Group)o)!=CLASS_COMPOSITEFIELD)
		DXErrorReturn(ERROR_BAD_PARAMETER, "#11660");

	    for (i=0; (oo=DXGetEnumeratedMember((Group)o, i, NULL)); i++)
		if (!traverse(oo, arg))
		    return ERROR;

	    break;

	case CLASS_FIELD:

	    colorArray = (Array)DXGetComponentValue((Field)o, COLORS);
	    if (! colorArray)
	    {
		DXSetError(ERROR_INTERNAL, "no colors found in image");
		return ERROR;
	    }

	    DXGetArrayInfo(colorArray, NULL, &type, NULL, &rank, shape);

	    if (type == TYPE_UBYTE || type == TYPE_BYTE)
	    {
		if (rank == 0 || (rank == 1 && shape[0] == 1))
		{
		    inType = IN_BYTE_SCALAR;
		}
		else if (rank == 1 && shape[0] == 3)
		{
		    inType = IN_BYTE_VECTOR;
		}
		else
		{
		    DXSetError(ERROR_DATA_INVALID,
			"byte images must be scalar or 1-vector or 3-vector");
		    return ERROR;
		}
	    }
	    else if (type == TYPE_FLOAT)
	    {
		if (rank != 1 || shape[0] != 3)
		{
		    DXSetError(ERROR_DATA_INVALID,
			"float images must be 3-vector");
		    return ERROR;
		}

		inType = IN_FLOAT_VECTOR;
	    }
	    else
	    {
		DXSetError(ERROR_DATA_INVALID,
			    "image fields must be type byte or type float");
		return ERROR;
	    }

	    src = (unsigned char *)DXGetArrayData(colorArray);


	    connections = (Array)DXGetComponentValue((Field)o, CONNECTIONS);
	    DXGetMeshOffsets((MeshArray)connections, offsets);
	    DXQueryGridConnections(connections, NULL, pcounts);

	    return _dxf_translateImage(o,
			    arg->width, arg->height,
			    arg->ox,    arg->oy,
			    offsets[0], offsets[1], pcounts[0], pcounts[1],
			    arg->i, arg->n,
			    arg->translation,
			    src, inType, arg->out);

	default:
	    break;
    }

    return OK;
}

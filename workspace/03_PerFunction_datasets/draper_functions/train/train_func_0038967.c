setextents(Object o, int *e)
{
    Object subo;
    Array a;
    int i, dim;
    int mo[2];
    int counts[2];


    for (i=0; (subo = DXGetEnumeratedMember((Group)o, i, NULL)); i++) {

	if (DXGetObjectClass(subo) != CLASS_FIELD) {
	    DXSetError(ERROR_DATA_INVALID,
		       "member of partitioned field is not a field");
	    return ERROR;
	}

	a = (Array)DXGetComponentValue((Field)subo, "connections");
	if (!a) {
	    DXSetError(ERROR_DATA_INVALID,
		       "field has no `connections' component");
	    return ERROR;
	}
	if (DXGetObjectClass((Object)a) != CLASS_ARRAY) {
	    DXSetError(ERROR_DATA_INVALID,
		       "connections component is not an Array object");
	    return ERROR;
	}

	if ((DXQueryGridConnections(a, &dim, NULL) == ERROR) ||
	    (dim != 2)) {
	    DXSetError(ERROR_DATA_INVALID,
		       "field must have regular 2d connections");
	    return ERROR;
	}
	DXQueryGridConnections(a, &dim, counts);

	if (!DXGetMeshOffsets((MeshArray)a, mo))
	    return ERROR;

	if (mo[0] + counts[0] > e[0])
	    e[0] = mo[0] + counts[0];
	if (mo[1] + counts[1] > e[1])
	    e[1] = mo[1] + counts[1];
    }

    return OK;
}

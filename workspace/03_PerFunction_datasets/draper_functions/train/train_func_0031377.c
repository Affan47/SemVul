ObjectVectorStats(Object o, int *vlen, float **minlist, float **maxlist)
{
    int i;
    Object subo;

    switch (DXGetObjectClass(o)) {
      case CLASS_ARRAY:
	return VectorStats(o, 0, vlen, 1, minlist, maxlist);

      case CLASS_FIELD:
	return VectorStats(o, 0, vlen, 1, minlist, maxlist);

      case CLASS_GROUP:
	switch (DXGetGroupClass((Group)o)) {
	  case CLASS_MULTIGRID:
	  case CLASS_SERIES:
	  case CLASS_COMPOSITEFIELD:


	    subo = DXGetEnumeratedMember((Group)o, 0, NULL);
	    if (VectorStats(subo, 0, vlen, 1, minlist, maxlist) == ERROR)
		return ERROR;

	    for (i=1; (subo = DXGetEnumeratedMember((Group)o, i, NULL)); i++) {
		if (VectorStats(subo, 1, vlen, 0, minlist, maxlist) == ERROR)
		    return ERROR;
	    }
	    return OK;

	  default:
	    return ERROR;
	}

      case CLASS_SCREEN:
	if (!DXGetScreenInfo((Screen)o, &subo, NULL, NULL))
	    return ERROR;

	return ObjectVectorStats(subo, vlen, minlist, maxlist);

      case CLASS_XFORM:
	if (!DXGetXformInfo((Xform)o, &subo, NULL))
	    return ERROR;

	return ObjectVectorStats(subo, vlen, minlist, maxlist);

      case CLASS_CLIPPED:
	if (!DXGetClippedInfo((Clipped)o, &subo, NULL))
	    return ERROR;

	return ObjectVectorStats(subo, vlen, minlist, maxlist);

      default:
	DXSetError(ERROR_BAD_PARAMETER, "#10190", "input");
	return ERROR;
    }


}

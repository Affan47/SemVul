_dxfMapToPlane(Object object, Vector *point, Vector *normal)
{
    Object copy = NULL;
    Object result = NULL;
    Plane  plane;

    if (! MakePlane(normal, point, &plane))
	goto error;

    copy = DXCopy(object, COPY_STRUCTURE);
    if (! copy)
	goto error;

    if (! DXCreateTaskGroup())
	goto error;

    if (! MapToPlaneObject(copy, plane, normal))
    {
	DXAbortTaskGroup();
	goto error;
    }

    if (! DXExecuteTaskGroup() || DXGetError() != ERROR_NONE)
	goto error;

    if (DXGetObjectClass(copy) != CLASS_FIELD)
    {
	result = MTP_Cleanup(copy);
	DXDelete(copy);

	if (DXGetError() != ERROR_NONE)
	    goto error;
    }
    else
	result = copy;

    return result;

error:
    DXDelete((Object)result);
    if (copy != object)
	DXDelete(copy);
    return NULL;
}

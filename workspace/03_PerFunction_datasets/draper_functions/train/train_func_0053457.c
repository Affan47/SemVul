DXSaveInvalidComponent(Field field, InvalidComponentHandle handle)
{
    Array array;
    char  sbuf[128];

    if (! handle->iName)
    {
	DXSetError(ERROR_INTERNAL, "unknown invalid component name");
	return ERROR;
    }

    sprintf(sbuf, "invalid %s", handle->iName);

    if (DXGetComponentValue(field, sbuf))
	DXDeleteComponent(field, sbuf);

    if (handle->type  == IC_ALL_UNMARKED &&
	handle->sense == IC_MARKS_INDICATE_INVALID)
    {
	return OK;
    }

    if (handle->type  == IC_ALL_MARKED &&
	handle->sense == IC_MARKS_INDICATE_VALID)
    {
	return OK;
    }

    array = DXGetInvalidComponentArray(handle);
    if (! array)
	return ERROR;

    if (! DXSetComponentValue(field, sbuf, (Object)array))
	return ERROR;

    return OK;
}

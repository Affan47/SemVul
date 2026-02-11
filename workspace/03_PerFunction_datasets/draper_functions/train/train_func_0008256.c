DXApplyTransform(Object object, Matrix *stack)
{
    if (! DXCreateTaskGroup())
	goto error;

    object = AT_traverse(object, stack);
    if (! object)
    {
	DXAbortTaskGroup();
	goto error;
    }

    if (! DXExecuteTaskGroup() || DXGetError() != ERROR_NONE)
	goto error;

    return object;

error:
    return NULL;
}

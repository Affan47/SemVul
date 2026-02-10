_dxfIrregShrink(Object object)
{
    int    i;
    Object child;
    struct shrinkTask task;
    Class  class;

    class = DXGetObjectClass(object);

    switch(class)
    {
	case CLASS_FIELD:

	    if (! DXEmptyField((Field)object))
		if (! IrregShrinkField((Pointer)&object))
		    goto error;

	    break;

        case CLASS_GROUP:

	    if (! DXCreateTaskGroup())
		goto error;

	    i = 0;
	    while (NULL !=
		(child = DXGetEnumeratedMember((Group)object, i++, NULL)))
	    {

		if (DXGetObjectClass(child), CLASS_FIELD)
		{
		    if (! DXEmptyField((Field)child))
		    {
			task.object = child;
			if (!DXAddTask(IrregShrinkField,
					(Pointer)&task, sizeof(task),1.0))
			{
			    DXAbortTaskGroup();
			    goto error;
			}
		    }

		}
		else
		{
		    if (! _dxfIrregShrink(child))
		    {
			DXAbortTaskGroup();
			goto error;
		    }
		}
	    }

	    if (! DXExecuteTaskGroup() || DXGetError() != ERROR_NONE)
		return NULL;

	    break;

	case CLASS_XFORM:

	    if (! DXGetXformInfo((Xform)object, &child, 0))
		goto error;

	    if (! _dxfIrregShrink(child))
		goto error;

	    break;

	default:

	    DXSetError(ERROR_DATA_INVALID, "unknown object");
	    goto error;
    }

    return object;

error:
    return NULL;
}

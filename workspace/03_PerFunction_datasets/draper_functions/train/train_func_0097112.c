_dxfPostObject(Object obj, int dir, Array comp)
{
    Class class;

    class = DXGetObjectClass(obj);
    if (class == CLASS_GROUP)
	class = DXGetGroupClass((Group)obj);

    switch(class)
    {
	case CLASS_FIELD:
	    if (! _dxfPostField((Field)obj, dir, comp))
		goto error;

	    break;

	case CLASS_GROUP:
	case CLASS_SERIES:
	case CLASS_MULTIGRID:
	{
	    Object child;
	    Group  group;
	    int    i;

	    group = (Group)obj;

	    i = 0;
	    while (NULL != (child = DXGetEnumeratedMember(group, i++, NULL)))
		if (! _dxfPostObject(child, dir, comp))
		    goto error;

	    break;
	}

	case CLASS_XFORM:
	{
	    Object child;

	    if (! DXGetXformInfo((Xform)obj, &child, 0))
		goto error;

	    if (! _dxfPostObject(child, dir, comp))
		goto error;

	    break;
	}

	case CLASS_CLIPPED:
	{
	    Object child;

	    if (! DXGetClippedInfo((Clipped)obj, &child, NULL))
		goto error;

	    if (! _dxfPostObject(child, dir, comp))
		goto error;

	    break;
	}

	case CLASS_COMPOSITEFIELD:
	{
	    int		i;
	    TaskArgs	args;
	    Group	group;
	    char	*compStrings[32];

	    if (! _dxfGetComponentList(obj, comp, dir, compStrings))
	    {
		if (DXGetError() != ERROR_NONE)
		    goto error;
	    }
	    else
	    {
		if (! DXGrowV(obj, 1, NULL, compStrings))
		    goto error;

		args.dir  = dir;
		args.comp = comp;

		if (! DXCreateTaskGroup())
		    goto error;

		group = (Group)obj;

		i = 0;
		while (NULL !=
		    (args.field = (Field)DXGetEnumeratedMember(group, i++, NULL)))
		    if (! DXAddTask(_dxfPostFieldTask,
					(Pointer)&args, sizeof(args), 1.0))
		    {
			DXAbortTaskGroup();
			goto error;
		    }

		if (! DXExecuteTaskGroup() || DXGetError() != ERROR_NONE)
		    goto error;

		if (! DXShrink(obj))
		    goto error;
	    }

	    break;
	}

	default:
	    DXSetError(ERROR_DATA_INVALID, "#11381");
	    goto error;
    }

    return obj;

error:

    return NULL;
}

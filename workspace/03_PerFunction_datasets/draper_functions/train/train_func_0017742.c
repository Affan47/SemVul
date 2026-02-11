SpawnVolumeTasks(Object o)
{
    int i;
    Object c;

    switch(DXGetObjectClass(o))
    {
	case CLASS_GROUP:
	    i = 0;
	    while (NULL != (c = DXGetEnumeratedMember((Group)o, i++, NULL)))
		if (! SpawnVolumeTasks(c))
		    return ERROR;

	    return OK;

	case CLASS_FIELD:
	    if (NULL == DXGetAttribute(o, "volume"))
		if (! DXAddTask(FieldVolumeTask, (Pointer)o, 0, 1.0))
		    return ERROR;
	    return OK;

	case CLASS_XFORM:
	    DXGetXformInfo((Xform)o, &c, NULL);
	    return SpawnVolumeTasks(c);

	case CLASS_CLIPPED:
	    DXGetClippedInfo((Clipped)o, &c, NULL);
	    return SpawnVolumeTasks(c);

	default:
	    return OK;
    }
}

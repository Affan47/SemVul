RS_Object(Object object, Object scale_o, Object min_o, Object max_o)
{
    Class class = DXGetObjectClass(object);
    if (class == CLASS_GROUP)
	class = DXGetGroupClass((Group)object);

    switch(class)
    {
	case CLASS_FIELD:
	{
	    float s, o;

	    if (DXEmptyField((Field)object))
		return OK;

	    if (! GetScaleAndOffset(object, scale_o, min_o, max_o, &s, &o))
	        return ERROR;

	    if (! RS_Field(object, s, o))
		return ERROR;

	   if (! DXSetFloatAttribute(object, "RubberSheet scale", s))
	       return ERROR;

	    return OK;
	}

	case CLASS_SERIES:
	case CLASS_COMPOSITEFIELD:
	case CLASS_MULTIGRID:
	{
	    float s, o;

	    if (! GetScaleAndOffset(object, scale_o, min_o, max_o, &s, &o))
	        return ERROR;

	    if (! RS_Field(object, s, o))
		return ERROR;

	   if (! DXSetFloatAttribute(object, "RubberSheet scale", s))
	       return ERROR;

	    return OK;
	}

	case CLASS_GROUP:
	{
	    Object c;
	    int    i;
	    Group  g = (Group)object;

	    for (i = 0; NULL != (c = DXGetEnumeratedMember(g, i, NULL)); i++)
		if (! RS_Object(c, scale_o, min_o, max_o))
		    return ERROR;

	    return OK;
	}

	case CLASS_XFORM:
	{
	    Object c;

	    if (! DXGetXformInfo((Xform)object, &c, NULL))
		return ERROR;

	    if (! RS_Object(c, scale_o, min_o, max_o))
		return ERROR;

	    return OK;
	}

	case CLASS_CLIPPED:
	{
	    Object c;

	    if (! DXGetClippedInfo((Clipped)object, &c, NULL))
		return ERROR;

	    if (! RS_Object(c, scale_o, min_o, max_o))
		return ERROR;

	    return OK;
	}

	case CLASS_SCREEN:
	{
	    Object c;

	    if (! DXGetScreenInfo((Screen)object, &c, NULL, NULL))
		return ERROR;

	    if (! RS_Object(c, scale_o, min_o, max_o))
		return ERROR;

	    return OK;
	}

	default:
	    DXSetError(ERROR_BAD_CLASS,
		"unknown object encountered in traversal");
	    return ERROR;
    }

}

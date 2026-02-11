GrowObject(Object object, int rings, Pointer fill, Array components)
{

    switch(DXGetObjectClass(object))
    {
	case CLASS_FIELD:
	{
	    break;
	}

	case CLASS_GROUP:
	{
	    if (DXGetGroupClass((Group)object) == CLASS_COMPOSITEFIELD)
	    {
		int regularity = IsRegular(object);

	        if (regularity == IS_REGULAR)
		{
		    if (!_dxfRegGrow(object, rings, fill, components))
			goto error;
		}
		else if (regularity == IS_NOT_REGULAR)
		{
		    if (! _dxfIrregGrow(object, rings, components))
			goto error;
		}
	    }
	    else
	    {
		Object c;
		Group g = (Group)object;
		int i;

		for (i=0; NULL != (c = DXGetEnumeratedMember(g, i, NULL)); i++)
		    if (! GrowObject(c, rings, fill, components))
			return NULL;
	    }
	    break;
	}

	case CLASS_XFORM:
	{
	    Object x;

	    if (! DXGetXformInfo((Xform)object, &x, NULL))
		goto error;

	    if (! GrowObject(x, rings, fill, components))
		goto error;
	}

	case CLASS_CLIPPED:
	{
	    Object x;

	    if (! DXGetClippedInfo((Clipped)object, &x, NULL))
		goto error;

	    if (! GrowObject(x, rings, fill, components))
		goto error;
	}

	default:
	    return NULL;
    }

    return object;

error:
    return NULL;
}

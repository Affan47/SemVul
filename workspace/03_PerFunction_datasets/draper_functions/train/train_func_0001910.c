doobject(Object o, Object whichone, int fexcept)
{
    Object newo = NULL;
    Object subo = NULL;

    switch (DXGetObjectClass(o)) {
      case CLASS_STRING:
	return doselect(o, whichone, IS_STRING, fexcept);

      case CLASS_GROUP:
	switch (DXGetGroupClass((Group)o)) {
	  case CLASS_SERIES:
	    return doselect(o, whichone, IS_SERIES, fexcept);

	  default:
	    return doselect(o, whichone, IS_GROUP, fexcept);

	}
	break;

#if DO_FIELDS
      case CLASS_FIELD:
        subo = DXGetComponentValue((Field)o, "data");
        if (!subo) {
            DXSetError(ERROR_DATA_INVALID,
  	       "no data component found in field for selecting list items");
            return NULL;
        }

	return doselect(subo, whichone, IS_LIST, fexcept);
#endif

      case CLASS_ARRAY:
	return doselect(o, whichone, IS_LIST, fexcept);

      case CLASS_XFORM:


	if (!DXGetXformInfo((Xform)o, &subo, NULL))
	    return NULL;

	if (!(subo = doobject(subo, whichone, fexcept)))
	    return NULL;

	if (!(newo = DXCopy(o, COPY_ATTRIBUTES))) {
	    DXDelete(subo);
	    return NULL;
	}

	if (!DXSetXformObject((Xform)newo, subo)) {
	    DXDelete(newo);
	    DXDelete(subo);
	    return NULL;
	}

       default:
         break;

       return newo;
    }

    DXSetError(ERROR_BAD_PARAMETER, "input must be group or list");
    return NULL;
}

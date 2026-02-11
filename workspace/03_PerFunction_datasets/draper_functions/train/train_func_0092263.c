Field__Exists2(Object o, char *name, char *name2)
{
    Object subo;
    Object subo2;
    Matrix m;
    int fixed, z;
    int i;

    if (!o)
	return NULL;

    switch(DXGetObjectClass(o)) {

      case CLASS_GROUP:
	for (i=0; (subo=DXGetEnumeratedMember((Group)o, i, NULL)); i++)
	    if (!Field__Exists2(subo, name, name2))
		return NULL;

	break;

      case CLASS_FIELD:


	if (DXGetComponentValue((Field)o, name)) {
	    if (!DXGetComponentValue((Field)o, name2))
		return NULL;
	}

	break;

      case CLASS_XFORM:
	if (!DXGetXformInfo((Xform)o, &subo, &m))
	    return NULL;

	if (!Field__Exists2(subo, name, name2))
	    return NULL;

	break;

      case CLASS_SCREEN:
	if (!DXGetScreenInfo((Screen)o, &subo, &fixed, &z))
	    break;

	if (!Field__Exists2(subo, name, name2))
	    return NULL;

	break;

      case CLASS_CLIPPED:
	if (!DXGetClippedInfo((Clipped)o, &subo, &subo2))
	    break;

	if (!Field__Exists2(subo, name, name2))
	    return NULL;

	break;

      default:


	break;

    }

    return o;
}

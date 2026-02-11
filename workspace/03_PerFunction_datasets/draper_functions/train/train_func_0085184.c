qcount(Object o)
{
    int nitems;

    CHECKIF(o, CLASS_ARRAY, "array");

    if (!DXGetArrayInfo((Array)o, &nitems, NULL, NULL, NULL, NULL))
	return NULL;

    return packint(nitems);
}

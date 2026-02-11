DXGetStringAttribute(Object o, char *name, char **x)
{
    String s;

    if (!(s = (String)DXGetAttribute(o, name)))
	return NULL;

    if (DXGetObjectClass((Object)s) != CLASS_STRING)
	return NULL;

    if (x)
	*x = DXGetString(s);

    return o;
}

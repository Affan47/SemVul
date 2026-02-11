DXSetStringAttribute(Object o, char *name, char *x)
{
    String s;
    s = DXNewString(x);
    if (!s)
	return NULL;
    if (!DXSetAttribute(o, name, (Object)s)) {
	DXDelete((Object)s);
	return NULL;
    }
    return o;
}

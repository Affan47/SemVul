DXGetEnumeratedAttribute(Object o, int n, char **name)
{
    struct attribute *a;
    if (!o)
	return NULL;
    if (n >= o->nattributes)
	return NULL;
    a = o->attributes + n;
    if (name)
	*name = a->name;
    return a->value;
}

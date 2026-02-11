initarray(Group g, char *member, char *component,
    int count, int mult)
{
    Field f;
    Array a;
    Pointer p;

    if (!(f = (Field) DXGetMember(g, member)))
	return NULL;

    if (!(a = (Array)DXGetComponentValue(f, component)))
	return NULL;

    if (!DXAddArrayData(a, 0, count * mult, NULL))
	return NULL;

    if (!(p = DXGetArrayData(a)))
	return NULL;

    return p;
}

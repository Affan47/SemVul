packit(int n, Type t, Category c, int rank, int *shape, Pointer p)
{
    Array a = NULL;

    a = DXNewArrayV(t, c, rank, shape);
    if (!a)
	return NULL;

    if (!DXAddArrayData(a, 0, n, p)) {
	DXDelete((Object)a);
	return NULL;
    }

    return a;
}

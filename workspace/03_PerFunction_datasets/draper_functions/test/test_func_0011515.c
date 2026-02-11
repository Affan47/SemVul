arrayitemsize(Type t, Category c, int rank, int *shape)
{
    int i, n;

    n = DXTypeSize(t) * DXCategorySize(c);
    for (i=0; i<rank; i++)
	n *= shape[i];

    return n;
}

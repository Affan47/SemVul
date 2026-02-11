_dxfArray_GetType(Array a, Type *t, Category *c, int *rank, int *shape)
{
    int i;

    if (t)
	*t = a->type;
    if (c)
	*c = a->category;
    if (rank)
	*rank = a->rank;
    if (shape)
	for (i=0; i<a->rank; i++)
	    shape[i] = a->shape[i];

    return (Object) a;
}

DXSetGroupTypeV(Group g, Type t, Category c, int rank, int *shape)
{
    int i;

    CHECK(g, CLASS_GROUP);


    g->typed = 1;
    g->type = t;
    g->category = c;
    g->rank = rank;
    DXFree((Pointer)g->shape);
    g->shape = (int *) DXAllocate(rank*sizeof(*shape));
    if (!g->shape)
	return NULL;
    for (i=0; i<rank; i++)
	g->shape[i] = shape[i];


    for (i=0; i<g->nmembers; i++)
	if (!type_check(g, g->members[i].value))
	    return NULL;

    return g;
}

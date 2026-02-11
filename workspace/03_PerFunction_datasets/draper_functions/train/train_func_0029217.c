DXQueryGridConnections(Array a, int *n, int *counts)
{
    Array as[100];
    int i, nn;


    if (DXGetArrayClass(a)!=CLASS_MESHARRAY)
	return NULL;


    if (!DXGetMeshArrayInfo((MeshArray)a, &nn, as))
	return NULL;
    ASSERT(nn<100);
    if (n)
	*n = nn;


    for (i=0; i<nn; i++) {
	if (DXGetArrayClass(as[i])!=CLASS_PATHARRAY)
	    return NULL;
	if (!DXGetPathArrayInfo((PathArray)as[i], counts? &(counts[i]) : NULL))
	    return NULL;
    }

    return a;
}

DXMakeGridConnectionsV(int n, int *counts)
{
    Array as[100];
    Array a;
    char et[32];
    int i;

    ASSERT(n<100);


    for (i=0; i<n; i++) {
	as[i] = (Array) DXNewPathArray(counts[i]);
	if (!as[i])
	    return NULL;
    }


    a = (Array) DXNewMeshArrayV(n, as);
    if (!a)
	return NULL;


    DXSetStringAttribute((Object)a, "element type", elementname(n, et));
    return a;
}

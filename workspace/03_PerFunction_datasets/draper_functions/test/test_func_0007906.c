MakeMap(int *indices, int n)
{
    int i, *map = DXAllocate(n*sizeof(int));
    if (! map)
	goto error;

    for (i = 0; i < n; i++)
	map[indices[i]] = i;

    return map;

error:
    return NULL;
}

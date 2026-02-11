getDumpableObjects(DumpableObject ***objs, int *numObjs)
{
	int			i,
				j;

	*objs = (DumpableObject **)
		pg_malloc(allocedDumpIds * sizeof(DumpableObject *));
	j = 0;
	for (i = 1; i < allocedDumpIds; i++)
	{
		if (dumpIdMap[i])
			(*objs)[j++] = dumpIdMap[i];
	}
	*numObjs = j;
}

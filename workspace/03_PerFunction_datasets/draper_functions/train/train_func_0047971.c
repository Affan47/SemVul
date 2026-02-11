xpmHashTableInit(table)
    xpmHashTable *table;
{
    xpmHashAtom *p;
    xpmHashAtom *atomTable;

    table->size = INITIAL_HASH_SIZE;
    table->limit = table->size / 3;
    table->used = 0;
    atomTable = (xpmHashAtom *) malloc(table->size * sizeof(*atomTable));
    if (!atomTable)
	return (XpmNoMemory);
    for (p = atomTable + table->size; p > atomTable;)
	*--p = NULL;
    table->atomTable = atomTable;
    return (XpmSuccess);
}

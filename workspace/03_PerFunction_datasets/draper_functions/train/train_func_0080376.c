xpmHashTableFree(table)
    xpmHashTable *table;
{
    xpmHashAtom *p;
    xpmHashAtom *atomTable = table->atomTable;
    for (p = atomTable + table->size; p > atomTable;)
	if (*--p)
	    free(*p);
    free(atomTable);
    table->atomTable = NULL;
}

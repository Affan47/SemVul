cuddZddAlignToBdd(
  DdManager * table )
{
    int *invpermZ;
    int M;
    int i,j;
    int result;


    if (table->sizeZ == 0)
	return(1);

    empty = table->zero;
    M = table->sizeZ / table->size;


    if (M * table->size != table->sizeZ)
	return(0);

    invpermZ = ALLOC(int,table->sizeZ);
    if (invpermZ == NULL) {
	table->errorCode = CUDD_MEMORY_OUT;
	return(0);
    }
    for (i = 0; i < table->size; i++) {
	int index = table->invperm[i];
	int indexZ = index * M;
	int levelZ = table->permZ[indexZ];
	levelZ = (levelZ / M) * M;
	for (j = 0; j < M; j++) {
	    invpermZ[M * i + j] = table->invpermZ[levelZ + j];
	}
    }


    cuddGarbageCollect(table,0);

    result = zddShuffle(table, invpermZ);
    FREE(invpermZ);

    zddFixTree(table,table->treeZ);
    return(result);

}

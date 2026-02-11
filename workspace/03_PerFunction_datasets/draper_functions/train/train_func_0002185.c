outputAllRetainerSet(FILE *prof_file)
{
    nat i, j;
    nat numSet;
    RetainerSet *rs, **rsArray, *tmp;


    numSet = 0;
    for (i = 0; i < HASH_TABLE_SIZE; i++)
	for (rs = hashTable[i]; rs != NULL; rs = rs->link) {
	    if (rs->id < 0)
		numSet++;
	}

    if (numSet == 0)
	return;


    rsArray = stgMallocBytes(numSet * sizeof(RetainerSet *),
			     "outputAllRetainerSet()");


    j = 0;
    for (i = 0; i < HASH_TABLE_SIZE; i++)
	for (rs = hashTable[i]; rs != NULL; rs = rs->link) {
	    if (rs->id < 0) {
		rsArray[j] = rs;
		j++;
	    }
	}

    ASSERT(j == numSet);


    for (i = numSet - 1; i > 0; i--) {
	for (j = 0; j <= i - 1; j++) {

	    if (rsArray[j]->id < rsArray[j + 1]->id) {
		tmp = rsArray[j];
		rsArray[j] = rsArray[j + 1];
		rsArray[j + 1] = tmp;
	    }
	}
    }

    fprintf(prof_file, "\nRetainer sets created during profiling:\n");
    for (i = 0;i < numSet; i++) {
	fprintf(prof_file, "SET %u = {", -(rsArray[i]->id));
	for (j = 0; j < rsArray[i]->num - 1; j++) {
	    printRetainer(prof_file, rsArray[i]->element[j]);
	    fprintf(prof_file, ", ");
	}
	printRetainer(prof_file, rsArray[i]->element[j]);
	fprintf(prof_file, "}\n");
    }

    stgFree(rsArray);
}

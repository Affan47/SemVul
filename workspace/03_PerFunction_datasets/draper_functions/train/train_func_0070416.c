make_random(
  DdManager * table,
  int  lower)
{
    int i,j;
    int	*used;
    int	next;

    used = ALLOC(int,numvars);
    if (used == NULL) {
	table->errorCode = CUDD_MEMORY_OUT;
	return(0);
    }
#if 0
#ifdef DD_STATS
    (void) fprintf(table->out,"Initial population before sifting\n");
    for (i = 0; i < 2; i++) {
	for (j = 0; j < numvars; j++) {
	    (void) fprintf(table->out," %2d",STOREDD(i,j));
	}
	(void) fprintf(table->out,"\n");
    }
#endif
#endif
    for (i = 2; i < popsize; i++) {
       	for (j = 0; j < numvars; j++) {
	    used[j] = 0;
	}


       	for (j = 0; j < numvars; j++) {
	    do {
		next = rand_int(numvars-1);
	    } while (used[next] != 0);
	    used[next] = 1;
	    STOREDD(i,j) = table->invperm[next+lower];
       	}
#if 0
#ifdef DD_STATS

	for (j = 0; j < numvars; j++) {
	    (void) fprintf(table->out," %2d",STOREDD(i,j));
	}
	(void) fprintf(table->out,"\n");
#endif
#endif
    }
    FREE(used);
    return(1);

}

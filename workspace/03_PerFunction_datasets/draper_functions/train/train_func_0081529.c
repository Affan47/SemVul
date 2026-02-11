Cudd_CofMinterm(
  DdManager * dd,
  DdNode * node)
{
    st_table	*table;
    double	*values;
    double	*result = NULL;
    int		i, firstLevel;

#ifdef DD_STATS
    unsigned long startTime;
    startTime = util_cpu_time();
    num_calls = 0;
    table_mem = sizeof(st_table);
#endif

    table = st_init_table(st_ptrcmp, st_ptrhash);
    if (table == NULL) {
	(void) fprintf(dd->err,
		       "out-of-memory, couldn't measure DD cofactors.\n");
	dd->errorCode = CUDD_MEMORY_OUT;
	return(NULL);
    }
    size = dd->size;
    values = ddCofMintermAux(dd, node, table);
    if (values != NULL) {
	result = ALLOC(double,size + 1);
	if (result != NULL) {
#ifdef DD_STATS
	    table_mem += (size + 1) * sizeof(double);
#endif
	    if (Cudd_IsConstant(node))
		firstLevel = 1;
	    else
		firstLevel = cuddI(dd,Cudd_Regular(node)->index);
	    for (i = 0; i < size; i++) {
		if (i >= cuddI(dd,Cudd_Regular(node)->index)) {
		    result[dd->invperm[i]] = values[i - firstLevel];
		} else {
		    result[dd->invperm[i]] = values[size - firstLevel];
		}
	    }
	    result[size] = values[size - firstLevel];
	} else {
	    dd->errorCode = CUDD_MEMORY_OUT;
	}
    }

#ifdef DD_STATS
    table_mem += table->num_bins * sizeof(st_table_entry *);
#endif
    if (Cudd_Regular(node)->ref == 1) FREE(values);
    st_foreach(table, cuddStCountfree, NULL);
    st_free_table(table);
#ifdef DD_STATS
    (void) fprintf(dd->out,"Number of calls: %d\tTable memory: %d bytes\n",
		  num_calls, table_mem);
    (void) fprintf(dd->out,"Time to compute measures: %s\n",
		  util_print_time(util_cpu_time() - startTime));
#endif
    if (result == NULL) {
	(void) fprintf(dd->out,
		       "out-of-memory, couldn't measure DD cofactors.\n");
	dd->errorCode = CUDD_MEMORY_OUT;
    }
    return(result);

}

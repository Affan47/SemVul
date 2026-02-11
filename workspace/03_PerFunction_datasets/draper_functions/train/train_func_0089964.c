Cudd_bddLargestPrimeUnate(
  DdManager *dd ,
  DdNode *f ,
  DdNode *phaseBdd )
{
    DdNode *res;
    int *phases;
    int retval;
    st_table *table;


    phases = ALLOC(int, dd->size);
    if (phases == NULL) return(NULL);
    retval = Cudd_BddToCubeArray(dd, phaseBdd, phases);
    if (retval == 0) {
        FREE(phases);
        return(NULL);
    }
    do {
        dd->reordered = 0;
        table = st_init_table(st_ptrcmp,st_ptrhash);
        if (table == NULL) {
            FREE(phases);
            return(NULL);
        }
	(void) ddBddShortestPathUnate(dd, f, phases, table);
        res = ddGetLargestCubeUnate(dd, f, phases, table);
        st_free_table(table);
    } while (dd->reordered == 1);

    FREE(phases);
    return(res);

}

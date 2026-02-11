Cudd_EpdCountMinterm(
  DdManager * manager,
  DdNode * node,
  int  nvars,
  EpDouble * epd)
{
    EpDouble	max, tmp;
    st_table	*table;
    int		status;

    background = manager->background;
    zero = Cudd_Not(manager->one);

    EpdPow2(nvars, &max);
    table = st_init_table(EpdCmp, st_ptrhash);
    if (table == NULL) {
	EpdMakeZero(epd, 0);
	return(CUDD_OUT_OF_MEM);
    }
    status = ddEpdCountMintermAux(Cudd_Regular(node),&max,epd,table);
    st_foreach(table, ddEpdFree, NULL);
    st_free_table(table);
    if (status == CUDD_OUT_OF_MEM) {
	EpdMakeZero(epd, 0);
	return(CUDD_OUT_OF_MEM);
    }
    if (Cudd_IsComplement(node)) {
	EpdSubtract3(&max, epd, &tmp);
	EpdCopy(&tmp, epd);
    }
    return(0);

}

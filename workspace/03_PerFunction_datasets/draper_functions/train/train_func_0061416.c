Cudd_bddUnivAbstract(
  DdManager * manager,
  DdNode * f,
  DdNode * cube)
{
    DdNode	*res;

    if (bddCheckPositiveCube(manager, cube) == 0) {
	(void) fprintf(manager->err,
		       "Error: Can only abstract positive cubes\n");
	manager->errorCode = CUDD_INVALID_ARG;
	return(NULL);
    }

    do {
	manager->reordered = 0;
	res = cuddBddExistAbstractRecur(manager, Cudd_Not(f), cube);
    } while (manager->reordered == 1);
    if (res != NULL) res = Cudd_Not(res);

    return(res);

}

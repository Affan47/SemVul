Cudd_RecursiveDerefZdd(
  DdManager * table,
  DdNode * n)
{
    DdNode *N;
    int ord;
    DdNodePtr *stack = table->stack;
    int SP = 1;

    N = n;

    do {
#ifdef DD_DEBUG
	assert(N->ref != 0);
#endif

	cuddSatDec(N->ref);

	if (N->ref == 0) {
	    table->deadZ++;
#ifdef DD_STATS
	    table->nodesDropped++;
#endif
#ifdef DD_DEBUG
	    assert(!cuddIsConstant(N));
#endif
	    ord = table->permZ[N->index];
	    stack[SP++] = cuddE(N);
	    table->subtableZ[ord].dead++;
	    N = cuddT(N);
	} else {
	    N = stack[--SP];
	}
    } while (SP != 0);

}

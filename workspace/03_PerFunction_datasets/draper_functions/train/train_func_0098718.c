Cudd_FirstNode(
  DdManager * dd,
  DdNode * f,
  DdNode ** node)
{
    DdGen *gen;
    int size;


    if (dd == NULL || f == NULL) return(NULL);


    gen = ALLOC(DdGen,1);
    if (gen == NULL) {
	dd->errorCode = CUDD_MEMORY_OUT;
	return(NULL);
    }

    gen->manager = dd;
    gen->type = CUDD_GEN_NODES;
    gen->status = CUDD_GEN_EMPTY;
    gen->stack.sp = 0;
    gen->node = NULL;


    gen->stack.stack = cuddNodeArray(Cudd_Regular(f), &size);
    if (gen->stack.stack == NULL) {
	FREE(gen);
	dd->errorCode = CUDD_MEMORY_OUT;
	return(NULL);
    }
    gen->gen.nodes.size = size;


    if (gen->stack.sp < gen->gen.nodes.size) {
	gen->status = CUDD_GEN_NONEMPTY;
	gen->node = gen->stack.stack[gen->stack.sp];
	*node = gen->node;
    }

    return(gen);

}

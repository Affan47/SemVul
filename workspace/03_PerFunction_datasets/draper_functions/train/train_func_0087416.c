get_loop_print_by_line (LOOPSET *loop, int lno, int *err)
{
    LOOP_PRINT *prns;
    int i, np = loop->n_prints;

    for (i=0; i<np; i++) {
	if (loop->prns[i].lineno == lno) {
	    return &loop->prns[i];
	}
    }

    prns = realloc(loop->prns, (np + 1) * sizeof *prns);
    if (prns == NULL) {
	*err = E_ALLOC;
	return NULL;
    } else {
	loop->prns = prns;
    }

    loop_print_init(&loop->prns[np], lno);
    loop->n_prints += 1;

    return &loop->prns[np];
}

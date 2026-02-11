gridRepulse(Dt_t * dt, cell * cellp, Grid * grid)
{
    node_list *nodes = cellp->nodes;
    int i = cellp->p.i;
    int j = cellp->p.j;
    node_list *p;
    node_list *q;

    NOTUSED(dt);
#ifdef DEBUG
    if (Verbose >= 3) {
	prIndent();
	fprintf(stderr, "gridRepulse (%d,%d) : %d\n", i, j,
		gLength(cellp));
    }
#endif
    for (p = nodes; p != 0; p = p->next) {
	for (q = nodes; q != 0; q = q->next)
	    if (p != q)
		applyRep(p->node, q->node);
    }

    doNeighbor(grid, i - 1, j - 1, nodes);
    doNeighbor(grid, i - 1, j, nodes);
    doNeighbor(grid, i - 1, j + 1, nodes);
    doNeighbor(grid, i, j - 1, nodes);
    doNeighbor(grid, i, j + 1, nodes);
    doNeighbor(grid, i + 1, j - 1, nodes);
    doNeighbor(grid, i + 1, j, nodes);
    doNeighbor(grid, i + 1, j + 1, nodes);

    return 0;
}

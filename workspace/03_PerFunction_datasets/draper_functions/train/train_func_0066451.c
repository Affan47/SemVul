freeCompileProg (comp_prog *p)
{
    comp_block* bp;
    int i;

    if (!p) return;

    exclose (p->prog, 1);
    for (i = 0; i < p->n_blocks; i++) {
	bp = p->blocks + i;
	free (bp->node_stmts);
	free (bp->edge_stmts);
    }
    free (p->blocks);
    free (p);
}

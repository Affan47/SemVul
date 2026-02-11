rtree_dump_node(FILE * fp, struct Node *n, int with_z)
{
    int i, nn;

    fprintf(fp, "Node level=%d  count=%d\n", n->level, n->count);

    if (n->level > 0)
	nn = NODECARD;
    else
	nn = LEAFCARD;

    for (i = 0; i < nn; i++) {
	if (n->branch[i].child) {
	    fprintf(fp, "  Branch %d", i);
	    rtree_dump_branch(fp, &n->branch[i], with_z, n->level);
	}
    }

    return 0;
}

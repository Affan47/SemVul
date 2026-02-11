lift_edges (G, newnode)
graph *G;
node *newnode;
#endif
{
    node *n, *node_k;
    node *nodelist = G->nodelist;
    int nn = INODE(newnode);
    edge *e;
    int ei, einext;

#if PRINT_LEVEL
    printf ("Lift edges %i\n", nn); fflush (stdout);
#endif

    n = node_k = PNODE(newnode->blossom_root);
    do {
        ei = n->edg_list;
        n->edg_list = -1;
        for (; ei != -1; ei = einext) {
            e = PEDGE(ei/2);
            einext = e->ptrs[ei % 2];
	    if ((nodelist[e->nod1].blossom_parent == nn) &&
                (nodelist[e->nod2].blossom_parent == nn)) {
                e->ptrs[ei % 2] = n->edg_list;
                n->edg_list = ei;
            } else {
		if (e->nod1 == INODE(n)) {
		    e->nod1 = nn;
		} else {
		    e->nod2 = nn;
                }
                e->ptrs[ei % 2] = newnode->edg_list;
                newnode->edg_list = ei;
	    }
	}
	n = PNODE(n->blossom_next);
    } while (n != node_k);
    return 0;
}

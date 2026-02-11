label_penultimate (G, n, label)
graph *G;
node *n;
int label;
#endif
{

    node *n2;

    if (n->blossom_root == -1) {
	n->penultimate = label;
	return;
    }

    n2 = n;
    while (1) {
	if (n2->blossom_root != -1) {
	    n2 = PNODE(n2->blossom_root);
	} else {
	    n2->penultimate = label;
	    while (n2->blossom_next ==
                   PNODE(n2->blossom_parent)->blossom_root) {
		n2 = PNODE(n2->blossom_parent);
		if (n2 == n) return;
	    }
	    n2 = PNODE(n2->blossom_next);
	}
    }
}

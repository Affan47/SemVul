FindNGByNum(unsigned long ngnumber) {
    NGTENT *ngtp;
    NGTREENODE *curnode;

    curnode = NGTree;

    while (curnode) {
	if (curnode->ngnumber == ngnumber) {
	    ngtp = curnode->ngtp;
	    return ngtp->ngname;
	}
	if (curnode->ngnumber < ngnumber) {
	    curnode = curnode->right;
	} else {
	    curnode = curnode->left;
	}
    }

    return NULL;
}

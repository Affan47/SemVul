splaytree_delete(splay_tree *t, int i) {


    splay_tree * x;
    int tsize;

    if (t==NULL) return NULL;
    tsize = t->size;
    t = splaytree_splay(t, i);
    if (compare(i, t->key) == 0) {
	if (t->left == NULL) {
	    x = t->right;
	} else {
	    x = splaytree_splay(t->left, i);
	    x->right = t->right;
	}
	free(t);
	if (x != NULL) {
	    x->size = tsize-1;
	}
	return x;
    } else {
	return t;
    }
}

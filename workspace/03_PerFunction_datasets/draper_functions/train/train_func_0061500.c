vzt_wr_dsvzt_splay (vztint32_t i, vzt_wr_dsvzt_Tree * t) {


    vzt_wr_dsvzt_Tree N, *l, *r, *y;
    int dir;

    vzt_wr_dsvzt_success = 0;

    if (t == NULL) return t;
    N.left = N.right = NULL;
    l = r = &N;

    for (;;) {
	dir = cmp_l(i, t->item);
	if (dir < 0) {
	    if (t->left == NULL) break;
	    if (cmp_l_lt(i, t->left->item)) {
		y = t->left;
		t->left = y->right;
		y->right = t;
		t = y;
		if (t->left == NULL) break;
	    }
	    r->left = t;
	    r = t;
	    t = t->left;
	} else if (dir > 0) {
	    if (t->right == NULL) break;
	    if (cmp_l_gt(i, t->right->item)) {
		y = t->right;
		t->right = y->left;
		y->left = t;
		t = y;
		if (t->right == NULL) break;
	    }
	    l->right = t;
	    l = t;
	    t = t->right;
	} else {
	    vzt_wr_dsvzt_success=1;
	    break;
	}
    }
    l->right = t->left;
    r->left = t->right;
    t->left = N.right;
    t->right = N.left;
    return t;
}

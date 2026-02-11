G_update_cell_stats(const CELL * cell, int n, struct Cell_stats *s)
{
    CELL cat;
    register int p, q;
    int idx, offset;
    int N;
    register NODE *node, *pnode;
    register NODE *new_node;

    if (n <= 0)
	return 1;

    node = s->node;


    if ((N = s->N) == 0) {
	cat = *cell++;
	while (G_is_c_null_value(&cat)) {
	    s->null_data_count++;
	    cat = *cell++;
	    n--;
	}
	if (n > 0) {
	    N = 1;
	    if (cat < 0) {
		idx = -((-cat) >> SHIFT) - 1;
		offset = cat + ((-idx) << SHIFT) - 1;
	    }
	    else {
		idx = cat >> SHIFT;
		offset = cat - (idx << SHIFT);
	    }
	    fflush(stderr);
	    init_node(&node[1], idx, offset);
	    node[1].right = 0;
	    n--;
	}
    }
    while (n-- > 0) {
	cat = *cell++;
	if (G_is_c_null_value(&cat)) {
	    s->null_data_count++;
	    continue;
	}
	if (cat < 0) {
	    idx = -((-cat) >> SHIFT) - 1;
	    offset = cat + ((-idx) << SHIFT) - 1;
	}
	else {
	    idx = cat >> SHIFT;
	    offset = cat - (idx << SHIFT);
	}

	q = 1;
	while (q > 0) {
	    pnode = &node[p = q];
	    if (pnode->idx == idx) {
		pnode->count[offset]++;
		break;
	    }
	    if (pnode->idx > idx)
		q = pnode->left;
	    else
		q = pnode->right;
	}
	if (q > 0)
	    continue;


	N++;


	if (N >= s->tlen) {
	    node =
		(NODE *) G_realloc((char *)node,
				   sizeof(NODE) * (s->tlen += INCR));
	    pnode = &node[p];
	}


	init_node(new_node = &node[N], idx, offset);

	if (pnode->idx > idx) {
	    new_node->right = -p;
	    pnode->left = N;
	}
	else {
	    new_node->right = pnode->right;
	    pnode->right = N;
	}
    }
    s->N = N;
    s->node = node;

    return 0;
}

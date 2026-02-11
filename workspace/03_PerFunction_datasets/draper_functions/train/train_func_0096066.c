strong_search_predecessors(osi_set_t * l, setkey_t k, sh_node_pt * pa,
			   sh_node_pt * na)
{
    sh_node_pt x, x_next, old_x_next, y, y_next;
    setkey_t y_k;
    int i;

  retry:
    RMB();

    x = &l->head;
    for (i = NUM_LEVELS - 1; i >= 0; i--) {

	READ_FIELD(x_next, x->next[i]);

	if (is_marked_ref(x_next))
	    goto retry;

	for (y = x_next;; y = y_next) {

	    for (;;) {
		READ_FIELD(y_next, y->next[i]);
		if (!is_marked_ref(y_next))
		    break;
		y = get_unmarked_ref(y_next);
	    }

	    if (y == l->tail) break;
	    READ_FIELD(y_k, y->k);
	    if (compare_keys(l, y_k, k) >= 0)
		break;


	    x = y;
	    x_next = y_next;
	}


	if (x_next != y) {
	    old_x_next = CASPO(&x->next[i], x_next, y);
	    if (old_x_next != x_next)
		goto retry;
	}

	if (pa)
	    pa[i] = x;
	if (na)
	    na[i] = y;
    }

    return (y);
}

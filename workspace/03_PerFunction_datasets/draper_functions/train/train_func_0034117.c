osi_cas_skip_free(gc_global_t *gc_global, osi_set_t *l)
{
    setval_t v, new_v;
    sh_node_pt n;
    int i, level;
    ptst_t *ptst;

    ptst = critical_enter(gc_global);
    gc_t *gc = ptst->gc;
    while ((n = l->head.next[0]) != l->tail) {
	READ_FIELD(level, n->level);
	level = level & LEVEL_MASK;


	new_v = n->v;
	do {
	    v = new_v;
	    if (v == NULL)
		goto out;
	} while ((new_v = CASPO(&n->v, v, NULL)) != v);


	WEAK_DEP_ORDER_WMB();
	mark_deleted(n, level);

	for (i = level - 1; i >= 0; i--) {
	    if (CASPO(l->head.next[i], n, get_unmarked_ref(n->next[i])) != n) {
		if ((i != (level - 1)) || check_for_full_delete(n)) {
		    MB();
		    do_full_delete(ptst, l, n, i);
		}
		goto out;
	    }
	    free_node(ptst, n);
	}
    }
  out:
    critical_exit(ptst);
    ptst = critical_enter(gc_global);
    critical_exit(ptst);
    memset(l, 0x67, sizeof *l);
    free(l);
}

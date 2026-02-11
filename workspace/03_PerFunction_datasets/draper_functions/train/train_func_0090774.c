idtree_remove(struct idtree *idp, int id)
{
	struct idtree_layer *p;


	id &= MAX_ID_MASK;

	if (sub_remove(idp, (idp->layers - 1) * IDTREE_BITS, id) == -1) {
		return false;
	}

	if ( idp->top && idp->top->count == 1 &&
	     (idp->layers > 1) &&
	     idp->top->ary[0]) {

		p = idp->top->ary[0];
		idp->top->bitmap = idp->top->count = 0;
		free_layer(idp, idp->top);
		idp->top = p;
		--idp->layers;
	}
	while (idp->id_free_cnt >= IDTREE_FREE_MAX) {
		p = alloc_layer(idp);
		talloc_free(p);
	}
	return true;
}

make_subtree(GcxPar p, GtkTreeIter *parent, GtkTreeStore *store)
{
	GtkTreeIter iter;
	GcxPar pp;

	if (PAR_TYPE(p) != PAR_TREE) {
		err_printf("not a tree param\n");
		return;
	}

	pp = PAR(p)->child;
	while (pp != PAR_NULL) {
		if (PAR_TYPE(pp) == PAR_TREE) {
			iter = make_subtree_item(pp, parent, store);
			make_subtree(pp, &iter, store);
		} else {
			make_par_leaf(pp, parent, store);
		}
		pp = PAR(pp)->next;
	}
}

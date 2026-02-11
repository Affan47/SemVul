search(float alt, float vis, TransformInput *ti)
    {
	struct RBitem search_ti = set_alt_vis(alt, vis);
	struct RBitem *found_ti;

	found_ti = (struct RBitem *)rbtree_find(RBTree, &search_ti);
	if (found_ti) {
	    *ti = found_ti->ti;
	    return 1;
	}
	else
	    return 0;

    }

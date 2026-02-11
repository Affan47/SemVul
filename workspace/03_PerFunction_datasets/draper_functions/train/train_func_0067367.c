knot_zone_tree_remove(knot_zone_tree_t *tree,
                            const knot_dname_t *owner,
                          knot_node_t **removed)
{
	if (tree == NULL || owner == NULL) {
		return KNOT_EINVAL;
	}

	uint8_t lf[KNOT_DNAME_MAXLEN];
	knot_dname_lf(lf, owner, NULL);

	value_t *rval = hattrie_tryget(tree, (char*)lf+1, *lf);
	if (rval == NULL) {
		return KNOT_ENOENT;
	} else {
		*removed = (knot_node_t *)(*rval);
	}


	hattrie_del(tree, (char*)lf+1, *lf);
	return KNOT_EOK;
}

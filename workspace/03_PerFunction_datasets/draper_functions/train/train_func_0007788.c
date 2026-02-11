knot_zone_tree_get_less_or_equal(knot_zone_tree_t *tree,
                                       const knot_dname_t *owner,
                                       knot_node_t **found,
                                       knot_node_t **previous)
{
	if (tree == NULL || owner == NULL || found == NULL
	    || previous == NULL) {
		return KNOT_EINVAL;
	}

	uint8_t lf[KNOT_DNAME_MAXLEN];
	knot_dname_lf(lf, owner, NULL);

	value_t *fval = NULL;
	int ret = hattrie_find_leq(tree, (char*)lf+1, *lf, &fval);
	if (fval) *found = (knot_node_t *)(*fval);
	int exact_match = 0;
	if (ret == 0) {
		*previous = knot_node_get_previous(*found);
		exact_match = 1;
	} else if (ret < 0) {
		*previous = *found;
		*found = NULL;
	} else if (ret > 0) {


		hattrie_iter_t *i = hattrie_iter_begin(tree, 1);
		*previous = *(knot_node_t **)hattrie_iter_val(i);
		*previous = knot_node_get_previous(*previous);
		*found = NULL;
		hattrie_iter_free(i);
	}


	if (knot_node_rrset_count(*previous) == 0) {
		*previous = knot_node_get_previous(*previous);
	}

dbg_zone_exec_detail(
		char *name = knot_dname_to_str(owner);
		char *name_f = (*found != NULL)
			? knot_dname_to_str(knot_node_owner(*found))
			: "none";

		dbg_zone_detail("Searched for owner %s in zone tree.\n",
				name);
		dbg_zone_detail("Exact match: %d\n", exact_match);
		dbg_zone_detail("Found node: %p: %s.\n", *found, name_f);
		dbg_zone_detail("Previous node: %p.\n", *previous);

		free(name);
		if (*found != NULL) {
			free(name_f);
		}
);

	return exact_match;
}

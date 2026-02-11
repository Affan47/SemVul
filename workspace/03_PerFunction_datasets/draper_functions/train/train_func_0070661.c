knot_zone_contents_create_node(knot_zone_contents_t *contents,
                                   const knot_rrset_t *rr,
                                   knot_node_t **node)
{
	if (contents == NULL || rr == NULL || node == NULL) {
		return KNOT_EINVAL;
	}

	*node = knot_node_new(rr->owner, NULL, 0);
	if (*node == NULL) {
		return KNOT_ENOMEM;
	}


	int ret = KNOT_EOK;
	if (knot_rrset_is_nsec3rel(rr)) {
		ret = knot_zone_contents_add_nsec3_node(contents, *node, 1, 0);
	} else {
		ret = knot_zone_contents_add_node(contents, *node, 1, 0);
	}

	if (ret != KNOT_EOK) {
		dbg_xfrin("Failed to add new node to zone contents.\n");
		knot_node_free(node);
		return ret;
	}

	return ret;
}

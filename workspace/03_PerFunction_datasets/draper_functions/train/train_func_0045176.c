knot_zone_diff_remove_node(knot_changeset_t *changeset,
                                                const knot_node_t *node)
{
	if (changeset == NULL || node == NULL) {
		dbg_zonediff("zone_diff: remove_node: NULL parameters.\n");
		return KNOT_EINVAL;
	}

	dbg_zonediff("zone_diff: remove_node: Removing node:\n");
dbg_zonediff_exec_detail(
	knot_node_dump((knot_node_t *)node);
);

	const knot_rrset_t **rrsets = knot_node_rrsets(node);
	if (rrsets == NULL) {
		dbg_zonediff_verb("zone_diff: remove_node: "
		                  "Nothing to remove.\n");
		return KNOT_EOK;
	}

	dbg_zonediff_detail("zone_diff: remove_node: Will be removing %d RRSets.\n",
	              knot_node_rrset_count(node));


	for (uint i = 0; i < knot_node_rrset_count(node); i++) {
		int ret = knot_zone_diff_changeset_remove_rrset(changeset,
		                                            rrsets[i]);
		if (ret != KNOT_EOK) {
			dbg_zonediff("zone_diff: remove_node: Failed to "
			             "remove rrset. Error: %s\n",
			             knot_strerror(ret));
			free(rrsets);
			return ret;
		}
		if (knot_rrset_rrsigs(rrsets[i])) {

			ret = knot_zone_diff_changeset_remove_rrset(changeset,
						knot_rrset_rrsigs(rrsets[i]));
			if (ret != KNOT_EOK) {
				dbg_zonediff("zone_diff: remove_node: Cannot "
				             "remove RRSIG (%s).\n",
				       knot_strerror(ret));
				free(rrsets);
				return ret;
			}
		}
	}

	free(rrsets);

	return KNOT_EOK;
}

knot_zone_contents_create_diff(const knot_zone_contents_t *z1,
                                   const knot_zone_contents_t *z2,
                                   knot_changeset_t *changeset)
{
	if (z1 == NULL || z2 == NULL) {
		dbg_zonediff("zone_diff: create_changesets: NULL arguments.\n");
		return KNOT_EINVAL;
	}
	int ret = knot_zone_contents_diff(z1, z2, changeset);
	if (ret != KNOT_EOK) {
		dbg_zonediff("zone_diff: create_changesets: "
		             "Could not diff zones. "
		             "Reason: %s.\n", knot_strerror(ret));
		return ret;
	}

	dbg_zonediff("Changesets created successfully!\n");
	dbg_zonediff_detail("Changeset dump:\n");
dbg_zonediff_exec_detail(
	knot_zone_diff_dump_changeset(changeset);
);

	return KNOT_EOK;
}

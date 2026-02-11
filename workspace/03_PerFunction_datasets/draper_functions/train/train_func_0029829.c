vg_revert(struct volume_group *vg)
{
	struct metadata_area *mda;

	dm_list_iterate_items(mda, &vg->fid->metadata_areas_in_use) {
		if (mda->ops->vg_revert &&
		    !mda->ops->vg_revert(vg->fid, vg, mda)) {
			stack;
		}
	}

	if (!drop_cached_metadata(vg))
		log_error("Attempt to drop cached metadata failed "
			  "after reverted update for VG %s.", vg->name);

	if (!remote_revert_cached_metadata(vg))
		stack;
}

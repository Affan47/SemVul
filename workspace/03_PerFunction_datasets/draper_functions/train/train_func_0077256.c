_vg_commit_mdas(struct volume_group *vg)
{
	struct metadata_area *mda, *tmda;
	struct dm_list ignored;
	int failed = 0;
	int cache_updated = 0;


	dm_list_init(&ignored);
	dm_list_iterate_items_safe(mda, tmda, &vg->fid->metadata_areas_in_use)
		if (mda_is_ignored(mda))
			dm_list_move(&ignored, &mda->list);

	dm_list_iterate_items_safe(mda, tmda, &ignored)
		dm_list_move(&vg->fid->metadata_areas_in_use, &mda->list);


	dm_list_iterate_items(mda, &vg->fid->metadata_areas_in_use) {
		failed = 0;
		if (mda->ops->vg_commit &&
		    !mda->ops->vg_commit(vg->fid, vg, mda)) {
			stack;
			failed = 1;
		}

		if (!failed && !cache_updated) {
			lvmcache_update_vg(vg, 0);

			cache_updated = 1;
		}
	}
	return cache_updated;
}
